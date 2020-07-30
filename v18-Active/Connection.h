#ifndef CONNECTION_H
#define CONNECTION_H
#include <list>
#include <vector>


namespace NS_OCH {
class Circuit;
class Log;
class ServiceChain;
class AbstractLink;
// class NetMan;

class Connection: public OchObject {
	Connection();
	Connection(const Connection&); 
	const Connection& operator=(const Connection&);

public:
	typedef enum {
		REQUEST = 1,	// connection request, not set up yet
		SETUP = 2,		// being set up
		DROPPED = 4,	// rejected
		TORNDOWN = 8	// done
	} ConnectionState;

	typedef enum {
		FIXED_BACKHAUL = 0,
		MOBILE_FRONTHAUL = 1,
		FIXEDMOBILE_FRONTHAUL = 2,
		MOBILE_BACKHAUL = 3,
		FIXEDMOBILE_BACKHAUL = 4
	} ConnectionType;


			//LA:binary heap for connection
	class PConnComp: public less<Connection*>
	{
	public:
		bool operator()(Connection*& pLeft, 
						Connection*& pRight) const {
							return (pLeft->m_eBandwidth > pRight->m_eBandwidth);
		}
	};

	/*Connection(UINT nSeqNo, UINT nSrc, UINT nDst, SimulationTime, SimulationTime,
		BandwidthGranularity eBW, ProtectionClass ePC = PC_NoProtection);*/
	Connection(UINT nSeqNo, UINT nSrc, UINT nDst, SimulationTime, SimulationTime,
		double eBW, ProtectionClass ePC = PC_NoProtection);
	Connection(UINT nSeqNo, UINT nSrc, UINT nDst, SimulationTime tArrivalTime, SimulationTime tHoldingTime, 
		double eBW, double CPRIbw, ProtectionClass ePC, ConnectionType connType);
	virtual ~Connection();

	virtual const char* toString() const; //stampa le info riguardanti la connessione nella stringa che restituisce(pStr)
	virtual void dump(ostream& out) const; //stampa le info riguardanti la connessione tramite il metodo toString() e aggiunge anche lo status della connessione considerata
	void log(Log&); //a seconda della stato della connessione, aumenta il num di connessioni provisioned o bloccate
	//	void tearDown(NetMan*, bool);

//public:
	// common attributes
	UINT					m_nSequenceNo;		// sequence number
	UINT					m_nSrc;				// src node
	UINT					m_nDst;				// dst node
	//LA:commented as it's replaced with double type ebandwidth
	//BandwidthGranularity    m_eBandwidth;		// bandwidth granularity (-B: bandwidth requested)
	double					m_eBandwidth;		//LA:
	double					m_ConLat;			//LA:to keep value of latency for connection and compare it later
	//double					m_ServiceChainBw;	//LA:bandwidth for SC as it's so small couldn't use eBandwidth
	double					m_eCPRIBandwidth;		//LA:changed to double
	vector<int> m_Con_Wl;				//LA:wavelength occupied by this connection
	//BandwidthGranularity	m_eCPRIBandwidth;	// -B: CPRI bandwidth requested by mobile or fixed-mobile nodes
	ProtectionClass			m_eProtectionClass;	// type of protection
	ConnectionState			m_eStatus;			// status

	UINT					m_nHopCount;	// max. hop count

	Circuit					*m_pPCircuit;	// primary if unprotected
	Circuit					*m_pBCircuit;	// backup if protected (but not PAL)
	list<Circuit*>			m_pCircuits;	//-B: needed for connections requiring a capacity > OCLightpath
	
	list<AbstractLink*> NewPath;		//LA:to keep new path for the connection
	bool					Reprov;		//LA:bool variable to check if the connection needs to be reprovisioned or not	

	// attributes for given traffic

	// attributes for dynamic traffic
	SimulationTime			m_dArrivalTime;
	SimulationTime			m_dHoldingTime;
	SimulationTime			m_dRoutingTime;	//-B: delay due to routing
	bool					m_bBlockedDueToUnreach;
	bool					m_bBlockedDueToLatency; //-B
	bool					m_bBlockedDueToTx;
	bool					m_bBlockedDueToCapacity; //LA:
	int						m_Num_link;		//LA:number of links
	ConnectionType			m_eConnType;
	UINT					grooming; //-B: count all the times that grooming is performed (not sure if it is performed correctly)

	// attributes for later use
	bool					m_bCanBifurcate;	
	bool					m_bNodeDiversity;

	static UINT				g_pBWMap[NumberOfBWGranularity];
	ServiceChain			*m_SC;
};

};

#endif
