/*
 * Copyright (C) Roland Jax 2012-2016 <roland.jax@liwest.at>
 *
 * This file is part of ebusgate.
 *
 * ebusgate is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ebusgate is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ebusgate. If not, see http://www.gnu.org/licenses/.
 */

#include <LogHandler.h>
#include "LogConsole.h"
#include "LogFile.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>

using std::istringstream;
using std::ostringstream;
using std::endl;
using std::setw;
using std::setfill;
using std::left;

extern map<Level, string> LevelNames;

LogHandler& LogHandler::getLogHandler()
{
	static LogHandler logHandler;
	return (logHandler);
}

LogHandler::~LogHandler()
{
	while (m_sinks.size() > 0)
		delSink(*(m_sinks.begin()));
}

void LogHandler::start()
{
	m_thread = thread(&LogHandler::run, this);
}

void LogHandler::stop()
{
	if (m_thread.joinable())
	{
		m_logMessages.enqueue(nullptr);
		m_thread.join();
	}
}

Level LogHandler::getLevel() const
{
	return (m_level);
}

void LogHandler::setLevel(const Level& level)
{
	m_level = level;
}

void LogHandler::setLevel(const string& level)
{
	m_level = calcLevel(level);
}

void LogHandler::addConsole()
{
	addSink(new LogConsole());
}

void LogHandler::addFile(const string& file)
{
	addSink(new LogFile(file));
}

void LogHandler::log(const LogMessage* logMessage)
{
	m_logMessages.enqueue(logMessage);
}

LogHandler::LogHandler()
{
}

void LogHandler::run()
{
	while (true)
	{
		const LogMessage* message = m_logMessages.dequeue();
		if (message == nullptr) break;

		if (m_level >= message->getLevel())
		{
			ostringstream ostr;

			ostr << "[" << message->getTime() << "] " << setw(5) << setfill(' ') << left
				<< LevelNames[(Level) message->getLevel()] << " " << message->getFunction() << " "
				<< message->getText() << endl;

			for (const auto& sink : m_sinks)
				sink->write(ostr.str());
		}

		delete message;
	}
}

void LogHandler::addSink(LogSink* sink)
{
	vector<LogSink*>::iterator it = find(m_sinks.begin(), m_sinks.end(), sink);

	if (it == m_sinks.end()) m_sinks.push_back(sink);

}

void LogHandler::delSink(const LogSink* sink)
{
	vector<LogSink*>::iterator it = find(m_sinks.begin(), m_sinks.end(), sink);

	if (it == m_sinks.end()) return;

	m_sinks.erase(it);
	delete sink;
}
