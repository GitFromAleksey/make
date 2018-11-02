#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

static const u32 dataSize = 8;
typedef cmn::array< u8, dataSize > Data;

static Data packData(u64 dataBytes, u8 len)
{
	Data packedData;
	for(u8 i = 0; i < len; i++)
	{
		packedData[i] = (u8)(dataBytes >> (i * 8));
	}
	return packedData;
}

static u64 unpackData(Data dataArray)
{
	u64 unpackedData = 0;
	for(u8 i = 0; i < dataSize; i++)
	{
		unpackedData |= ((u64)dataArray[i] << (i * 8));
	}
	return unpackedData;
}

//	TODO: присваивать 0 всем элементам массива
//	как-нибудь более интеллектуально
static void fillDataByZeros(Data &data)
{
	for (u8 i = 0; i < dataSize; i++)
	{
		data[i] = 0;
	}
}

typedef struct
{
	u8 major;
	u8 minor;
	u16 revision;
} EPASVersion;

// Priority_0 наивысший
// Priority_7 низший
enum MessagePriority {
	Priority_0,
	Priority_1,
	Priority_2,
	Priority_3,
	Priority_4,
	Priority_5,
	Priority_6,
	Priority_7
};

enum MessageType {
	Request,
	Nack,
	Sync_ctrl,
	Sync_param,
	Reg_ctrl_1,
	Reg_param_1,
	Warnings,
	Errors,
	Control,
	Retcontrol,
	Devstate,
	Program_info
};

struct J1939PGN
{
	//! PDU format
	//! формат PDU. PF<240(0xF0) - адресное,
	//! иначе - групповое (PDU2)
	u8 pf;

	//! PDU specific
	//! PS(PDU Specific), DA(Destination)
	//! Address
	u8 ps;

	J1939PGN()
	{
		pf = 0;
		ps = 0;
	}

	u32 getAsU32()
	{
		return (u32)(((u16)pf << 8) | ps);
	}
};

struct J1939idParams
{
	J1939PGN		pgn;
	MessagePriority	priority;
	u8				sa;			//source address
};

u32 composeCanId(J1939idParams *idParams)
{
	u32 id = 0;

	const bool reserved = 0;
	const bool dataPage = 0;

	id = (idParams->priority << 26) +
			(reserved << 25) +
			(dataPage << 24) +
			(idParams->pgn.pf << 16) +
			(idParams->pgn.ps << 8) +
			(idParams->sa << 0);

	return id;
}

J1939idParams decomposeCanId (u32 *id)
{
	J1939idParams idParams;

	idParams.priority = (MessagePriority)(*id >> 26);
	idParams.sa = *id;
	idParams.pgn.ps = *id >> 8;
	idParams.pgn.pf = *id >> 16;

	return idParams;
}

#endif /* SRC_UTILS_H_ */
