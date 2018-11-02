#ifndef TESTS_EPS_MOCK_H_
#define TESTS_EPS_MOCK_H_

#include "../src/const.h"
#include "gaz_eps_protocol.h"
#include "utils.h"

namespace GazEpsProtocolMock
{
class MockEps: public GazEpsProtocol::User
{
public:

	MockEps(){init();}
	~MockEps(){}

	//! Устанавливает уставку положения
	//! \param[in] pos уставка положения (-1.0...1.0)
	virtual void setSteeringWheelPositionRef(f32 pos)
	{
		pos += 1.0;
		pos *= 1000;
		setSteeringWheelPosition((u16)pos);
	}

	//! Возвращает текущее положение
	//! \return текущее положение  (-1.0...1.0)
	virtual f32 getSteeringWheelPosition()
	{
		f32 answer;
		answer = (f32)getSteeringWheelPositionInBytes();
		answer -= 1000.0;
		return answer / 1000;
	}

	//! Устанавливает ограничение скорости
	//! \param[in] speed ограничение скорости (0...1.0)
	virtual void setSteeringWheelSpeedLimit(f32 speed)
	{
		speed *= 100;
		u8 speedInPercent;
		speedInPercent = (u8)speed;
		setSteeringSpeed(speedInPercent);
	}

	//! Возвращает текущую скорость
	//! \return текущая скорость (0...1.0)
	virtual f32 getSteeringWheelSpeed()
	{
		f32 speedInPercents;
		speedInPercents = (f32)getSteeringSpeed();
		return speedInPercents / 100;
	}

	virtual void getVersion(u8 &major, u8 &minor, u16 &revision, u32 &checksum)
	{
		major = version.major;
		minor = version.minor;
		revision = version.revision;
		checksum = getChecksum();
	}

	void setVersion(EPASVersion version)
	{
		this->version = version;
	}

	void init()
	{
		clearAllWarnings();
		clearAllErrors();
		setLastWarningNumber(0);
		setLastErrorNumber(0);
		regCtrlReceived = false;

		setStoredSteeringWheelPosition(1000);
		setStoredSteeringSpeed(0);

		setSteeringWheelPosition(1000);
		setSteeringSpeed(0);

		setChecksum(0xDEADFACE);

		setSelfDiagState(DEVSTATE_SELFDIAG_ALL_OK);
		EPASVersion version;
		version.major = 0;
		version.minor = 0;
		version.revision = 1;
		setVersion(version);
		setId(EPAS_ID);

		setPidTermsPosition(0);
		setPidTermsSpeed(0);

		if (!checkCriticalErrors())
		{
			setState(Mode::Enum::NORMAL);
		}
		else
		{
			setState(Mode::Enum::FAILURE);
		}
	}

	bool checkCriticalErrors()
	{
		return false;
	}

	void setId(u8 id)
	{
		this->id = id;
	}

	u8 getId()
	{
		return this->id;
	}

	void setSelfDiagState(u8 selfDiagState)
	{
		this->selfDiagState = selfDiagState;
	}

	u8 getSelfDiagState()
	{
		return this->selfDiagState;
	}

	void setRegCtrlReceived(bool received)
	{
		regCtrlReceived = received;
	}

	bool getRegCtrlReceived()
	{
		return regCtrlReceived;
	}

	void setSteeringWheelPosition(u16 position_bytes)
	{
		steeringWheelPosition = position_bytes;
	}

	u16 getSteeringWheelPositionInBytes()
	{
		return steeringWheelPosition;
	}

	bool setSteeringSpeed(u8 speed_bytes)
	{
		steeringSpeed = speed_bytes;
	}

	u8 getSteeringSpeed()
	{
		return steeringSpeed;
	}

	void setStoredSteeringWheelPosition(u16 stored_position_bytes)
	{
		storedSteeringWheelPosition = stored_position_bytes;
	}

	u16 getStoredSteeringWheelPosition()
	{
		return storedSteeringWheelPosition;
	}

	void setStoredSteeringSpeed(u8 stored_speed_bytes)
	{
		storedSteeringSpeed = stored_speed_bytes;
	}

	u8 getStoredSteeringSpeed()
	{
		return storedSteeringSpeed;
	}

	virtual void goToNormalMode()
	{
		setState(Mode::Enum::NORMAL);
	}

	virtual void goToRemoteControlMode()
	{
		setState(Mode::Enum::REMOTE_CONTROL);
	}

	virtual Mode::Enum getMode()
	{
		return state;
	}

	void setState(Mode::Enum state)
	{
		this->state = state;
	}

	//! сбрасывает флаг ошибки
	virtual void clearError(u8 code)
	{
		errors &= ~((u64)1 << code);
	}

	virtual void clearAllErrors()
	{
		errors = 0;
	}

	//! Получает флаги ошибок
	virtual u64 getErrorMask()
	{
		return errors;
	}

	virtual void clearWarning(u8 code)
	{
		warnings &= ~((u64)1 << code);
	}

	virtual void clearAllWarnings()
	{
		warnings = 0;
	}

	virtual u64 getWarningMask()
	{
		return warnings;
	}

    //! Возвращает текущие коэффициенты ПИ-регулятора положения
    //! \return байты 0, 1 - предельная уставка скорости в формате 2^16
//! \return байты 2, 3 - коэффициент пропорционального звена в формате 2^Qp
    //! \return байт 4 - степенной показатель Qp
//! \return байты 5, 6 - коэффициент интегрирующего звена в формате 2^Qi
    //! \return байт 7 - степенной показатель Qi
    virtual u64 getPidTermsPosition()
    {
    	u64 packedTerms = 0;
    	packedTerms =	getPidPositionSpeedLimit() +
    					((u64)getPidPositionProportionalTerm() << 16) +
						((u64)getPidPositionIntegralTerm() << 40);
    	return packedTerms;
    }

    //! Возвращает текущие коэффициенты ПИ-регулятора скорости
    //! \return байты 0, 1 - предельная уставка момента в формате 2^16
//! \return байты 2, 3 - коэффициент пропорционального звена в формате 2^Qp
    //! \return байт 4 - степенной показатель Qp
//! \return байты 5, 6 - коэффициент интегрирующего звена в формате 2^Qi
    //! \return байт 7 - степенной показатель Qi
    virtual u64 getPidTermsSpeed()
    {
    	u64 packedTerms = 0;
    	packedTerms =	getPidSpeedMomentumLimit() +
    					((u64)getPidSpeedProportionalTerm() << 16) +
						((u64)getPidSpeedIntegralTerm() << 40);
    	return packedTerms;
    }

    //! Устанавливает коэффициенты ПИ-регулятора положения
    //! Байты 0, 1 - предельная уставка скорости в формате 2^16
    //! Байты 2, 3 - коэффициент пропорционального звена в формате 2^Qp
    //! Байт 4 - степенной показатель Qp
    //! Байты 5, 6 - коэффициент интегрирующего звена в формате 2^Qi
    //! Байт 7 - степенной показатель Qi
    virtual void setPidTermsPosition(u64 positionTerms)
    {
    	u64 newTerms = positionTerms;

    	setPidPositionSpeedLimit((u16)newTerms);
		setPidPositionProportionalTerm((u32)(newTerms >> 16) & 0xFFFFFF);
		setPidPositionIntegralTerm((u32)(newTerms >> 40) & 0xFFFFFF);
    }

    //! Устанавливает коэффициенты ПИ-регулятора скорости
    //! Байты 0, 1 - предельная уставка момента в формате 2^16
    //! Байты 2, 3 - коэффициент пропорционального звена в формате 2^Qp
    //! Байт 4 - степенной показатель Qp
    //! Байты 5, 6 - коэффициент интегрирующего звена в формате 2^Qi
    //! Байт 7 - степенной показатель Qi
    virtual void setPidTermsSpeed(u64 speedTerms)
    {
    	u64 newTerms = speedTerms;

    	setPidSpeedMomentumLimit((u16)newTerms);
    	setPidSpeedProportionalTerm((u32)(newTerms >> 16) & 0xFFFFFF);
    	setPidSpeedIntegralTerm((u32)(newTerms >> 40) & 0xFFFFFF);
    }

	void setWarning(u8 warnNumber)
	{
		warnings |= (u64)1 << warnNumber;
	}

	void setError(u8 errNumber)
	{
		errors |= (u64)1 << errNumber;
	}

	void setLastWarningNumber(u8 lastWarn)
	{
		this->lastWarningNumber = lastWarn;
	}

	u8 getLastWarningNumber()
	{
		return this->lastWarningNumber;
	}

	void setLastErrorNumber(u8 lastError)
	{
		this->lastErrorNumber = lastError;
	}

	u8 getLastErrorNumber()
	{
		return this->lastErrorNumber;
	}

	u32 getChecksum() {
		return checksum;
	}

	void setChecksum(u32 checksum) {
		this->checksum = checksum;
	}

	u32 getPidPositionIntegralTerm() {
		return pidPositionIntegralTerm;
	}

	void setPidPositionIntegralTerm(u32 pidPositionIntegralTerm) {
		this->pidPositionIntegralTerm = pidPositionIntegralTerm;
	}

	u32 getPidPositionProportionalTerm() {
		return pidPositionProportionalTerm;
	}

	void setPidPositionProportionalTerm(u32 pidPositionProportionalTerm) {
		this->pidPositionProportionalTerm = pidPositionProportionalTerm;
	}

	u16 getPidPositionSpeedLimit() {
		return pidPositionSpeedLimit;
	}

	void setPidPositionSpeedLimit(u16 pidPositionSpeedLimit) {
		this->pidPositionSpeedLimit = pidPositionSpeedLimit;
	}

	u32 getPidSpeedIntegralTerm() {
		return pidSpeedIntegralTerm;
	}

	void setPidSpeedIntegralTerm(u32 pidSpeedIntegralTerm) {
		this->pidSpeedIntegralTerm = pidSpeedIntegralTerm;
	}

	u16 getPidSpeedMomentumLimit() {
		return pidSpeedMomentumLimit;
	}

	void setPidSpeedMomentumLimit(u16 pidSpeedMomentumLimit) {
		this->pidSpeedMomentumLimit = pidSpeedMomentumLimit;
	}

	u32 getPidSpeedProportionalTerm() {
		return pidSpeedProportionalTerm;
	}

	void setPidSpeedProportionalTerm(u32 pidSpeedProportionalTerm) {
		this->pidSpeedProportionalTerm = pidSpeedProportionalTerm;
	}

private:
	u8 id;
	Mode::Enum state;
	u8 selfDiagState;
	bool regCtrlReceived;
	EPASVersion version;
	u64 warnings;
	u64 errors;
	u8 lastWarningNumber;
	u8 lastErrorNumber;

	u32 checksum;

	u16 steeringWheelPosition;
	u8 steeringSpeed;

	u16 storedSteeringWheelPosition;
	u8 storedSteeringSpeed;

	u16 pidPositionSpeedLimit;
	u32 pidPositionProportionalTerm;
	u32 pidPositionIntegralTerm;

	u16 pidSpeedMomentumLimit;
	u32 pidSpeedProportionalTerm;
	u32 pidSpeedIntegralTerm;
};
}

#endif
