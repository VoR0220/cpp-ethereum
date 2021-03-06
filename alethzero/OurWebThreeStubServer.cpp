/*
	This file is part of cpp-ethereum.

	cpp-ethereum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	cpp-ethereum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file OurWebThreeStubServer.cpp
 * @author Gav Wood <i@gavwood.com>
 * @date 2014
 */

#include "OurWebThreeStubServer.h"

#include <QMessageBox>
#include <libwebthree/WebThree.h>
#include "MainWin.h"
using namespace std;
using namespace dev;
using namespace dev::eth;

OurWebThreeStubServer::OurWebThreeStubServer(jsonrpc::AbstractServerConnector& _conn, dev::WebThreeDirect& _web3, std::vector<dev::KeyPair> const& _accounts):
	WebThreeStubServer(_conn, _web3, _accounts), m_web3(&_web3)
{}

std::string OurWebThreeStubServer::shh_newIdentity()
{
	dev::KeyPair kp = dev::KeyPair::create();
	emit onNewId(QString::fromStdString(toJS(kp.sec())));
	return toJS(kp.pub());
}

bool OurWebThreeStubServer::authenticate(dev::TransactionSkeleton const& _t) const
{
	return true;

	// To get the balance of the sender
	cnote << "Sender has ETH: " << m_web3->ethereum()->postState().balance(_t.from);

	Main* main; // don't know this yet, should be a member and set at construction time by Main, who will construct us.

	h256 contractCodeHash = m_web3->ethereum()->postState().codeHash(_t.to);

	if (contractCodeHash == EmptySHA3)
	{
		// recipient has no code - nothing special about this transaction.
		// TODO: show basic message for value transfer.
		return true;	// or whatever.
	}

	std::string natspecJson = main->lookupNatSpec(contractCodeHash);

	if (natspecJson.empty())
	{
		// TODO: HUGE warning - we don't know what this will do!
		return false;	// or whatever.
	}

	// otherwise it's a transaction to contract for which we have the natspec:
	// determine the actual message (embellish with real data) and ask user.

//	QMessageBox::question();

	return true;
}
