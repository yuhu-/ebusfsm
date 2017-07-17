/*
 * Copyright (C) Roland Jax 2012-2017 <roland.jax@liwest.at>
 *
 * This file is part of ebuscpp.
 *
 * ebuscpp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ebuscpp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ebuscpp. If not, see http://www.gnu.org/licenses/.
 */

#ifndef LIBEBUS_STATE_H
#define LIBEBUS_STATE_H

#include "EbusFSM.h"

namespace libebus
{

#define STATE_ERR_TRANSMIT   -14 // An 'eBus' error occurred while sending this sequence
#define STATE_ERR_SEQUENCE   -13 // The passed Sequence contains an error
#define STATE_ERR_ADDRESS    -12 // The master address of the sequence and 'FSM' must be equal
#define STATE_ERR_MASTER     -11 // Active sending is only as master possible

#define STATE_INF_EBUS_ON      1 // ebus connected
#define STATE_INF_EBUS_OFF     2 // ebus disconnected
#define STATE_INF_EBUS_LOCK    3 // ebus locked
#define STATE_INF_EBUS_FREE    4 // ebus freed
#define STATE_INF_MSG_INGORE   5 // message ignored
#define STATE_INF_DEV_FLUSH    6 // device flushed

#define STATE_WRN_BYTE_DIF    11 // written/read byte difference
#define STATE_WRN_ARB_LOST    12 // arbitration lost
#define STATE_WRN_PRI_FIT     13 // priority class fit -> retry
#define STATE_WRN_PRI_LOST    14 // priority class lost
#define STATE_WRN_ACK_NEG     15 // received ACK byte is negative -> retry
#define STATE_WRN_RECV_RESP   16 // received response is invalid -> retry
#define STATE_WRN_RECV_MSG    17 // at me addressed message is invalid
#define STATE_WRN_NOT_DEF     18 // at me addressed message is undefined
#define STATE_WRN_NO_FUNC     19 // function not implemented

#define STATE_ERR_LOCK_FAIL   21 // lock ebus failed
#define STATE_ERR_ACK_NEG     22 // received ACK byte is negative -> failed
#define STATE_ERR_ACK_WRONG   23 // received ACK byte is wrong
#define STATE_ERR_NN_WRONG    24 // received NN byte is wrong
#define STATE_ERR_RECV_RESP   25 // received response is invalid -> failed
#define STATE_ERR_RESP_CREA   26 // creating response message failed
#define STATE_ERR_RESP_SEND   27 // sending response message failed

class State
{

public:
	virtual int run(EbusFSM* fsm) = 0;
	virtual const string toString() const = 0;

	static const string stateMessage(const int state);

protected:
	virtual ~State();

	static long m_reopenTime;
	static int m_lockCounter;
	static int m_lockRetries;
	static Sequence m_sequence;
	static EbusMessage* m_activeMessage;
	static EbusMessage* m_passiveMessage;

	static void changeState(EbusFSM* fsm, State* state);
	static int read(EbusFSM* fsm, unsigned char& byte, const long sec, const long nsec);
	static int write(EbusFSM* fsm, const unsigned char& byte);
	static int writeRead(EbusFSM* fsm, const unsigned char& byte, const long timeout);

	static void reset(EbusFSM* fsm);

};

} // namespace libebus

#endif // LIBEBUS_STATE_H
