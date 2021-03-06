#pragma once

#include "jni.h"
#include "ThostFtdcMdApi.h"
#include <fstream> 

using namespace std;

class CtpMdSpi : public CThostFtdcMdSpi
{
public:
	CtpMdSpi(JavaVM *jvm, jobject jobj);
	~CtpMdSpi();

	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected();
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	virtual void OnFrontDisconnected(int nReason);
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///订阅询价应答
	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///取消订阅询价应答
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
	///询价通知
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

private:
	CThostFtdcMdApi* pMdApi;

	JavaVM *jvm;
	jobject jobj;

	jmethodID OnFrontConnected_mid;
	jmethodID OnFrontDisconnected_mid;
	jmethodID OnHeartBeatWarning_mid;
	jmethodID OnRspUserLogin_mid;
	jmethodID OnRspUserLogout_mid;
	jmethodID OnRspError_mid;
	jmethodID OnRspSubMarketData_mid;
	jmethodID OnRspUnSubMarketData_mid;
	jmethodID OnRspSubForQuoteRsp_mid;
	jmethodID OnRspUnSubForQuoteRsp_mid;
	jmethodID OnRtnDepthMarketData_mid;
	jmethodID OnRtnForQuoteRsp_mid;

	void MdSpiMethodSigInit();
};