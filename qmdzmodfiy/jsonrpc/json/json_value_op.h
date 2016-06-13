#ifndef __JSON_VALUE_OP_H__
#define __JSON_VALUE_OP_H__

// ��jsonStr��string������char szArry[]
#define COPYJSONSTR_TO_STRARRAY(strArry, jsonStr) if (!jsonStr.isNull() && jsonStr.isString()) {	\
	const char *pCStr = jsonStr.asCString();			\
	int iLen = strlen(pCStr); if (iLen)					\
{													\
	strncpy(strArry, pCStr, sizeof(strArry) / sizeof(strArry[0])); \
}													\
}													\
else												\
{													\
	_asm int 3			\
}	

#define COPYJSONSTR_TO_STRARRAY_NB(strArry, jsonStr) if (!jsonStr.isNull() && jsonStr.isString()) {	\
	const char *pCStr = jsonStr.asCString();			\
	int iLen = strlen(pCStr); if (iLen)					\
{													\
	strncpy(strArry, pCStr, sizeof(strArry) / sizeof(strArry[0])); \
}													\
}

// ��jsonStr��string������wchar_t wstrArry[]
#define COPYJSONSTR_TO_WSTRARRAY(wstrArry, jsonStr) if (!jsonStr.isNull() && jsonStr.isString()) {	\
	const char *pCStr = jsonStr.asCString();			\
	int iLen = strlen(pCStr); if (iLen)					\
{													\
	std::vector<wchar_t> vecWCH;					\
	if (UTF8ToUnicode(vecWCH, pCStr, iLen))			\
{												\
	vecWCH.push_back(0);						\
	wcsncpy(wstrArry, &vecWCH[0], sizeof(wstrArry) / sizeof(wstrArry[0])); \
}												\
}													\
}													\
else												\
{													\
	_asm int 3			\
}	
#define COPYJSONSTR_TO_WSTRARRAY_NB(wstrArry, jsonStr) if (!jsonStr.isNull() && jsonStr.isString()) {	\
	const char *pCStr = jsonStr.asCString();			\
	int iLen = strlen(pCStr); if (iLen)					\
{													\
	std::vector<wchar_t> vecWCH;					\
	if (UTF8ToUnicode(vecWCH, pCStr, iLen))			\
{												\
	vecWCH.push_back(0);						\
	wcsncpy(wstrArry, &vecWCH[0], sizeof(wstrArry) / sizeof(wstrArry[0])); \
}												\
}													\
}

// ��jsonStr��string������std::wstring stdwstring
#define COPYJSONSTR_TO_STDWSTRING(stdwstring, jsonStr) if (!jsonStr.isNull() && jsonStr.isString()) {	\
	const char *pCStr = jsonStr.asCString();			\
	int iLen = strlen(pCStr); if (iLen)					\
{													\
	std::vector<wchar_t> vecWCH;					\
	if (UTF8ToUnicode(vecWCH, pCStr, iLen))			\
{												\
	vecWCH.push_back(0);						\
	stdwstring = &vecWCH[0];					\
}												\
}													\
}													\
else												\
{													\
	_asm int 3				\
}
#define COPYJSONSTR_TO_STDWSTRING_NB(stdwstring, jsonStr) if (!jsonStr.isNull() && jsonStr.isString()) {	\
	const char *pCStr = jsonStr.asCString();			\
	int iLen = strlen(pCStr); if (iLen)					\
{													\
	std::vector<wchar_t> vecWCH;					\
	if (UTF8ToUnicode(vecWCH, pCStr, iLen))			\
{												\
	vecWCH.push_back(0);						\
	stdwstring = &vecWCH[0];					\
}												\
}													\
}

// ��jsonStr��string������wchar_t wstrArry[]
#define COPYJSONSTR_TO_INT(iDst, jsonStr) if (!jsonStr.isNull() && jsonStr.isString()) {	\
	const char *pCStr = jsonStr.asCString();			\
	int iLen = strlen(pCStr); if (iLen)					\
{													\
	std::vector<wchar_t> vecWCH;					\
	if (UTF8ToUnicode(vecWCH, pCStr, iLen))			\
{												\
	vecWCH.push_back(0);						\
	iDst = _wtoi(&vecWCH[0]); \
}												\
}													\
}													\
else												\
{													\
	_asm int 3			\
}
// ������Ͳ��ԣ���Ϊnull��ֱ��������
#define COPYJSONSTR_TO_INT_NB(iDst, jsonStr) if (!jsonStr.isNull() && jsonStr.isString()) {	\
	const char *pCStr = jsonStr.asCString();			\
	int iLen = strlen(pCStr); if (iLen)					\
{													\
	std::vector<wchar_t> vecWCH;					\
	if (UTF8ToUnicode(vecWCH, pCStr, iLen))			\
{												\
	vecWCH.push_back(0);						\
	iDst = _wtoi(&vecWCH[0]); \
}												\
}													\
}	

// ��jsonStr��string������int64
#define COPYJSONSTR_TO_INT64(iDst, jsonStr) if (!jsonStr.isNull() && jsonStr.isString()) {	\
	const char *pCStr = jsonStr.asCString();			\
	int iLen = strlen(pCStr); if (iLen)					\
{													\
	std::vector<wchar_t> vecWCH;					\
	if (UTF8ToUnicode(vecWCH, pCStr, iLen))			\
{												\
	vecWCH.push_back(0);						\
	iDst = _wtoi64(&vecWCH[0]); \
}												\
}													\
}													\
else												\
{													\
	_asm int 3			\
}
// ������Ͳ��ԣ���Ϊnull��ֱ��������
#define COPYJSONSTR_TO_INT64_NB(iDst, jsonStr) if (!jsonStr.isNull() && jsonStr.isString()) {	\
	const char *pCStr = jsonStr.asCString();			\
	int iLen = strlen(pCStr); if (iLen)					\
{													\
	std::vector<wchar_t> vecWCH;					\
	if (UTF8ToUnicode(vecWCH, pCStr, iLen))			\
{												\
	vecWCH.push_back(0);						\
	iDst = _wtoi64(&vecWCH[0]); \
}												\
}													\
}

// ��jsonStr��double������int64
#define COPYJSONREAL_TO_INT64(fDst, jsonV) if (!jsonV.isNull() && jsonV.isDouble()) {	\
	double fNum = jsonV.asDouble();			\
	fDst = (__int64)fNum; \
}													\
else												\
{													\
	_asm int 3			\
}
// ������Ͳ��ԣ���Ϊnull��ֱ��������
#define COPYJSONNREAL_TO_INT64_NB(iDst, jsonStr)if (!jsonV.isNull() && jsonV.isDouble()) {	\
	double fNum = jsonV.asDouble();			\
	fDst = (__int64)fNum; \
}													

// ��jsonInt��ֵ������int
#define COPYJSONINT_TO_INT(iDest, jsonInt) if (!jsonInt.isNull() && jsonInt.isInt()) {			\
	iDest = jsonInt.asInt();							\
}													\
else												\
{													\
	_asm int 3			\
}
// ������Ͳ��ԣ���Ϊnull��ֱ��������
#define COPYJSONINT_TO_INT_NB(iDest, jsonInt) if (!jsonInt.isNull() && jsonInt.isInt()) {			\
	iDest = jsonInt.asInt();							\
}													

// ��jsonInt��ֵ������int
#define COPYJSONINT_TO_BOOL(bDest, jsonInt) if (!jsonInt.isNull() && jsonInt.isInt()) {			\
	bDest = jsonInt.asInt() != 0;							\
}													\
else												\
{													\
	_asm int 3			\
}
// ������Ͳ��ԣ���Ϊnull��ֱ��������
#define COPYJSONINT_TO_BOOL_NB(bDest, jsonInt) if (!jsonInt.isNull() && jsonInt.isInt()) {			\
	bDest = jsonInt.asInt() != 0;							\
}

// ��jsonBoolean��ֵ������bool
#define COPYJSONBOOL_TO_BOOL(bDest, jsonBoolean) if (!jsonBoolean.isNull() && jsonBoolean.isBool()) {			\
	bDest = jsonBoolean.asBool();							\
}													\
else												\
{													\
	_asm int 3				\
}	
// ������Ͳ��ԣ���Ϊnull��ֱ��������
#define COPYJSONBOOL_TO_BOOL_NB(bDest, jsonBoolean) if (!jsonBoolean.isNull() && jsonBoolean.isBool()) {			\
	bDest = jsonBoolean.asBool();							\
}

// ��json�쳣��Ϣ������std::wstring wstr
#define JRETOSTDWSTR(e, wstr) {		\
	std::vector<wchar_t> vecUN;		\
	const char *pExc = e.what();	\
	UTF8ToUnicode(vecUN, pExc, strlen(pExc));	\
	vecUN.push_back(0);				\
	wstr = &vecUN.front();			\
}

	





#endif