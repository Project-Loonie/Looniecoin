// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers 
// Copyright (c) 2015-2017 The Loonie developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
/*
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(259201, uint256("1c9121bf9329a6234bfd1ea2d91515f19cd96990725265253f4b164283ade5dd"))
    (424998, uint256("f31e381eedb0ed3ed65fcc98cc71f36012bee32e8efd017c4f9fb0620fd35f6b"))
    (616764, uint256("29dd0bd1c59484f290896687b4ffb6a49afa5c498caf61967c69a541f8191557")) //first block to use modifierV2
    (623933, uint256("c7aafa648a0f1450157dc93bd4d7448913a85b7448f803b4ab970d91fc2a7da7"));
*/
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(0, uint256("0x00000a980907dfbdeb25abeed64d59cca87d7687876e74ed208c6b1e7e059d8a"));
	
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1543197839, // * UNIX timestamp of last checkpoint block
    0,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    500        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1543197900,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1543198000,
    0,
    0};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xd9;
        pchMessageStart[1] = 0x32;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0x6b;
        vAlertPubKey = ParseHex("04428b49c7b03b8faab32077bd9038d8e4516a83a0350713fd14ead7b1f4130ccbcbcbd9a0a156c1ab34bb84063494b436f317de3253ed021c0d771f51b418f753");
        nDefaultPort = 33447;  //33447
        bnProofOfWorkLimit = ~uint256(0) >> 15; // LNI starting difficulty is 1 / 2^12  //20
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 1250;
        nRejectBlockOutdatedMajority = 1450;
        nToCheckBlockUpgradeMajority = 1500;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // LNI: 1 minute // 1 day
        nTargetSpacing = 1 * 60;  // LNI: 60 sec
        nLastPOWBlock = 1000;
        nMaturity = 20;
        nMaturityMAX = 365*10*640;// Ten Years
        nMasternodeCountDrift = 20;
        nMasternodeColleteralLimxDev = 50000; //Params().MasternodeColleteralLimxDev()
        nModifierUpdateBlock = 1; // we use the version 2 for dmd
		nMaxMoneyOut = 130000000 * COIN;

        
		 
        const char* pszTimestamp = "If at first you don't succeed, try, try, try again - November, 2018";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("044d1dfacdc6d0826f03e8fb4f432546cf8577b6fa5ec5a712936c6569cd5d44768f123ed7e75b5fe91e8c55f149fcf56cd64792b48bdd096c3beec49fd29bd599") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1543197839;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 7091600;

        /*if(genesis.GetHash() != uint256("0x001"))
    {
      printf("MSearching for genesis block...\n");
      uint256 hashTarget;
      hashTarget.SetCompact(genesis.nBits);
      while(uint256(genesis.GetHash()) > uint256(hashTarget))
      {
          ++genesis.nNonce;
          if (genesis.nNonce == 0)
          {
              //printf("Mainnet NONCE WRAPPED, incrementing time");
              //std::cout << std::string("Mainnet NONCE WRAPPED, incrementing time:\n");
              ++genesis.nTime;
          }
          if (genesis.nNonce % 10000 == 0)
          {
              //printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
          }
      }
      printf("Mainnet block.nTime = %u \n", genesis.nTime);
      printf("Mainnet block.nNonce = %u \n", genesis.nNonce);
      printf("Mainnet block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
      printf("Mainnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
    }*/

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000a980907dfbdeb25abeed64d59cca87d7687876e74ed208c6b1e7e059d8a"));
        assert(genesis.hashMerkleRoot == uint256("0xb85a26eec5f714f58308a16b234a76add4414e46e737b7a3f60c7b5eaba9f31c"));

        vFixedSeeds.clear();
        vSeeds.clear();
	 //    vSeeds.push_back(CDNSSeedData("dnsseed.bit.loonies", "dnsseed.bit.loonies"));
		// vSeeds.push_back(CDNSSeedData("37.120.186.85", "37.120.186.85"));
		// vSeeds.push_back(CDNSSeedData("185.194.140.60", "185.194.140.60"));
		// vSeeds.push_back(CDNSSeedData("188.68.39.1", "188.68.39.1"));
		// vSeeds.push_back(CDNSSeedData("188.68.52.172", "188.68.52.172"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 48);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 25);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 2);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x67)(0x62)(0xB2)(0xF4).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x44)(0xb0)(0xAD)(0xF8).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109 	0x8000006d
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x41).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false; //true
        fAllowMinDifficultyBlocks = true; //true
        fDefaultConsistencyChecks = false;
        fRequireStandard = true; // true
        fMineBlocksOnDemand = false; //false
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;
		
	/*
        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false; 
        fTestnetToBeDeprecatedFieldRPC = true;
	*/

        nPoolMaxTransactions = 3;
        strSporkKey = "04d569777d5472fe729fdea1b6fc8f9d679cb46b1eb313da3aa03764a883a5530b90bcb3b1b6ef543f16e49142fc910de8aa45fbd74ab5cc518612da8a48f9f0a7";
        //strSporkKey = "04B433E6598390C992F4F022F20D3B4CBBE691652EE7C48243B81701CBDB7CC7D7BF0EE09E154E6FCBF2043D65AF4E9E97B89B5DBAF830D83B9B7F469A6C45A717";
        strmixTXPoolDummyAddress = "LVthn6oPwLRGZk2iAu226xkQURGEMkui5K";
        nStartMasternodePayments = 1543195886; //now 26 Nov 2018
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x99;
        pchMessageStart[1] = 0x73;
        pchMessageStart[2] = 0xbb;
        pchMessageStart[3] = 0xa6;
        vAlertPubKey = ParseHex("04e1d8aa8ac86ccd8a00529c5080bc47a50215bb4a4179716e7ff708853ff73de91bbe5decd314018d398887e29011d88a76001696f97dc1f3bed7092c3e407940");
        nDefaultPort = 33547;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // LNI: 1 day
        nTargetSpacing = 1 * 60;  // LNI: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
		

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1543197900;
        genesis.nNonce = 7882620;

        /*if(genesis.GetHash() != uint256("0x"))
    {
      printf("MSearching for genesis block...\n");
      uint256 hashTarget;
      hashTarget.SetCompact(genesis.nBits);
      while(uint256(genesis.GetHash()) > uint256(hashTarget))
      {
          ++genesis.nNonce;
          if (genesis.nNonce == 0)
          {
              //printf("Maintest NONCE WRAPPED, incrementing time");
              //std::cout << std::string("Maintest NONCE WRAPPED, incrementing time:\n");
              ++genesis.nTime;
          }
          if (genesis.nNonce % 10000 == 0)
          {
              //printf("Maintest: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
          }
      }
      printf("testnet block.nTime = %u \n", genesis.nTime);
      printf("testnet block.nNonce = %u \n", genesis.nNonce);
      printf("testnet block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
      printf("testnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
}*/

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000164337bd26f58fdfe4430d885cb2f272d5ca3079743766f6c2d60b78b29"));

        vFixedSeeds.clear();
        vSeeds.clear();
	//vSeeds.push_back(CDNSSeedData("dnsseed.bit.loonies", "dnsseed.bit.loonies"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet loonie addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet loonie script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet loonie BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet loonie BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet loonie BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false; 
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "045e87a1216ed3874515f5044e46d74c1bac67f2d72e042101ab4024a4851c038d306431cd5c137af0704a9ff6da716e8f96d24e71a3d3527c0e8c0fab5af2263f";
        strmixTXPoolDummyAddress = "y57cqfGRk9kRyDRNeJiLtYVHbvhXrNbmox";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x6b;
        pchMessageStart[1] = 0x62;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0xed;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 1 * 60; // Loonie: 1 day
        nTargetSpacing = 1 * 60;        // Loonie: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1543198000;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 7590263;

        /*if(genesis.GetHash() != uint256("0x"))
    {
      printf("MSearching for genesis block...\n");
      uint256 hashTarget;
      hashTarget.SetCompact(genesis.nBits);
      while(uint256(genesis.GetHash()) > uint256(hashTarget))
      {
          ++genesis.nNonce;
          if (genesis.nNonce == 0)
          {
              // printf("REGnet NONCE WRAPPED, incrementing time");
              // std::cout << std::string("REGnet NONCE WRAPPED, incrementing time:\n");
              ++genesis.nTime;
          }
          if (genesis.nNonce % 10000 == 0)
          {
              // printf("REGnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
          }
      }
      printf("reg block.nTime = %u \n", genesis.nTime);
      printf("reg block.nNonce = %u \n", genesis.nNonce);
      printf("reg block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
      printf("reg block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
    }*/

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 33549;
        assert(hashGenesisBlock == uint256("0x00000a89fd933ceaf7d2734b57ef33e959e25b3fa3f192930764ad4ea9151b2f"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 33550;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
