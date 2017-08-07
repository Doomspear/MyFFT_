#pragma once

#include "Defines.h"
#include "AstarNode.h"
#include "Obj.h"

class CAstarHandler
{
private:
	POBJ							m_pUser;
	POBJ							m_pStartTile;		//시작
	POBJ							m_pDestTile	;		//목표
	
	list< PASTARNODE >				m_listAstOpen;
	list< PASTARNODE >				m_listAstClose;		
	list< PASTARNODE >				m_listAstBest;		
	list< PASTARNODE >				m_listAstTemp;		
	list< POBJ >					m_listTileBest;		//베스트 타일 리스트

	list< PASTARNODE >::iterator	it;
	ASTARNODE						m_Tracker;			//추적자	

	
	vector< POBJ >*					m_pvecPTile;		//타일
	_INT							m_iAmount;			//행 수

	
private:
	PASTARNODE CreateNode(POBJ pTile, POBJ pParent, POBJ pDest);

public:
	void SetUser(POBJ pUser);
	void SetVecTile(vector<POBJ>* pvec);

	void CAstarHandler::AstarStart(POBJ pUser, POBJ pTarget);
	void AstarStart(POBJ pUser, POBJ pStartTile, POBJ pDestTile);
	void CheckTracker();
	
	void ClearTemp();
	void ClearClose();
	void ClearOpen();
	void ClearBest();

public:
	list< POBJ >* GetBest();
	
public:
	void Progress();
	void Release();

//singletone
private:
	static CAstarHandler* m_pInst;
public:
	inline static CAstarHandler* GetInst()
	{
		if ( m_pInst == NULL )
			m_pInst = new CAstarHandler;

		return m_pInst;
	}
	inline void DestroyInst()
	{
		if ( m_pInst != NULL )
		{
			delete m_pInst;
			m_pInst = NULL;
		}
	}
private:
	CAstarHandler(void);
	~CAstarHandler(void);
};