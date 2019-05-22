#include <iostream>
#include <string>

#include "Blockchain.hpp"
#include "Wallet.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using Utils::bytesToStr;
using Utils::hashToBytes;
using Utils::Uint256ToBytes;

typedef vector<Transaction> Txs;

void printTx(Transaction &tx);
void printBlock(Block &block);
void printAcc(Account &a);
string abridgeBytes(Bytes bytes, size_t length = 4);

Blockchain instantiateBlockchain(Txs txList) {
	;;
}

int main() {
	const Uint256 dummy("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDBAAEDCE6AF48A03BBFD25E8CD0364141");
	Uint256 GAIA_PRIV_INT(CurvePoint::ORDER);
	GAIA_PRIV_INT.shiftRight1(true);
	cout << bytesToStr(Uint256ToBytes(GAIA_PRIV_INT)) << endl;

	vector<string> privKeys = {
		"E9873D79C6D87DC0FB6A5778633389F4453213303DA61F20BD67FC233AA33262",
		"B8EF4E4640FBBD526166FF260EB65EC2B3B60064CCE2DA9747201BA201E90F7F",
		"7A6D055110F4296A85E8122B32F87AD32A58CF9BB73435088102638D7DECE1F2"
	};

	Wallet wallet1;

	for(string key : privKeys) {
		cout << "Adding account using key: " << key << endl;
		wallet1.addAccount(Account(key));
	}
	cout << endl;

	cout << "Wallet 1 - Current account::::\n";
	printAcc(*wallet1.currentAcc);
	cout << endl;

	Wallet wallet2;
	wallet2.addAccount(Account(privKeys[1]));
	cout << "Wallet 2 - Current account::::\n";
	printAcc(*wallet2.currentAcc);
	cout << endl;

	cout << "Wallet 1 - Current account::::\n";
	printAcc(*wallet1.currentAcc);
	cout << endl;

	Wallet wallet3;
	wallet3.addAccount(Account(privKeys[2]));
	cout << "Wallet 3 - Current account::::\n";
	printAcc(*wallet3.currentAcc);
	cout << endl;

	Transaction tx1 = wallet1.createTransaction(wallet3.currentAcc->pub, 10);
	Transaction tx2 = wallet3.createTransaction(wallet2.currentAcc->pub, 10);
	Transaction tx3 = wallet2.createTransaction(wallet1.currentAcc->pub, 10);
	wallet1.signTransaction(tx1);
	//printTx(tx1);

	Block block1(vector<Transaction>({tx1, tx2, tx3}), Transaction::DEFAULT_NONCE, Transaction::DEFAULT_NONCE); 
	printBlock(block1);

	cout << "Instantiating blockchain...\n";
	Blockchain blockchain;

	cout << "Pushing genesis block...";
	blockchain.genesis(wallet1.currentAcc->pub);
	//	blockchain.addBlock(block1);

	return 0;
}


//Txs getDummyTxs(Wallet &wallet) {
Txs getDummyTxs() {

}


string txSummary(Transaction &tx) {
	string result;
	result += "from: " + abridgeBytes(tx.fromKey.toBytes());
	result += ",  to: " + abridgeBytes(tx.toKey.toBytes());
	result += ",  amnt: " + std::to_string(tx.amount);

	return result;
}

// @param length: number of bytes to display at either end
string abridgeBytes(Bytes bytes, size_t length) {
	Bytes l, r;
	Bytes::iterator front = bytes.begin();
	Bytes::iterator back = bytes.end();
	--back;

	for(int i=0; i<length; i++, ++front, --back) {
		l.push_back(*front);
		r.insert(r.begin(), *back);
	}

	return "0x" + bytesToStr(l) + "..." + bytesToStr(r);
}

void printTx(Transaction &tx) {

	cout << " ~~~ Tx Details ~~~ \n";
	cout << "from:\t" << bytesToStr(tx.fromKey.toBytes());
	cout << "\nto:\t" << bytesToStr(tx.toKey.toBytes());
	cout << "\namnt:\t" << tx.amount;
	cout << "\nsig:\t" << bytesToStr(tx.signature->toBytes());
	cout << endl;
}

void printBlock(Block &block) {
	char d = 176;
	string bookend = "_-_-_-_-_-_-_-_-_-_-_-_";
	string head = "";
	head += bookend + " Block " + bookend;

	string summary = "";
	for(auto &tx : block.txList) {
		summary += "     " + txSummary(tx) + "\n";	
	}

	cout << head << endl;
	//cout << "myHash:\t" << abridgeBytes(hashToBytes(block.getHash()));
	//cout << "\nprevHash:\t" << abridgeBytes(hashToBytes(block.getPrevHash()));
	cout << "blockHash:\t" << bytesToStr(hashToBytes(block.getHash()));
	cout << "\nprevHash:\t" << bytesToStr(hashToBytes(block.getPrevHash()));
	cout << endl << summary;
	cout << endl;
}

void printAcc(Account &a) {
	cout << " ~~~ Account Details ~~~ \n";
	cout << "priv:\t" << bytesToStr(a.priv.toBytes());
	cout << "\npub:\t" << bytesToStr(a.pub.toBytes());
	cout << endl;

}
