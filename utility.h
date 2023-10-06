#ifndef UTILITY_H
#define UTILITY_H

#include <QObject>
#include <QMetaEnum>
#include <cstdint>
#include "vescinterface.h"

#define FE_WGS84 (1.0 / 298.257223563) // earth flattening (WGS84)
#define RE_WGS84 6378137.0             // earth semimajor axis (WGS84) (m)

class Utility : public QObject
{
    Q_OBJECT

public:
    explicit Utility(QObject *parent = nullptr);

    static double map(double x, double in_min, double in_max, double out_min, double out_max);
    static float throttle_curve(float val, float curve_acc, float curve_brake, int mode);
    static bool autoconnectBlockingWithProgress(VescInterface *vesc, QWidget *parent = 0);
    //    Q_INVOKABLE static void checkVersion(VescInterface *vesc = 0);
    //    Q_INVOKABLE static QString fwChangeLog();
    Q_INVOKABLE static QString vescToolChangeLog();
    Q_INVOKABLE static QString aboutText();
    Q_INVOKABLE static QString uuid2Str(QByteArray uuid, bool space);
    Q_INVOKABLE static bool requestFilePermission();
    Q_INVOKABLE static void keepScreenOn(bool on);
    Q_INVOKABLE static bool waitSignal(QObject *sender, QString signal, int timeoutMs);
    //    Q_INVOKABLE static QString detectAllFoc(VescInterface *vesc,
    //                                            bool detect_can, double max_power_loss, double min_current_in,
    //                                            double max_current_in, double openloop_rpm, double sl_erpm);
    Q_INVOKABLE static bool resetInputCan(VescInterface *vesc, QVector<int> canIds);
    //    Q_INVOKABLE static bool setBatteryCutCan(VescInterface *vesc, QVector<int> canIds,
    //                                             double cutStart, double cutEnd);
    //    Q_INVOKABLE static bool setBatteryCutCanFromCurrentConfig(VescInterface *vesc, QVector<int> canIds);
    //    Q_INVOKABLE static bool setInvertDirection(VescInterface *vesc, int canId, bool inverted);
    //    Q_INVOKABLE static bool getInvertDirection(VescInterface *vesc, int canId);
    //    Q_INVOKABLE static QString testDirection(VescInterface *vesc, int canId, double duty, int ms);
    Q_INVOKABLE static bool restoreConfAll(VescInterface *vesc, bool can, bool mc, bool app);
    Q_INVOKABLE static bool almostEqual(double A, double B, double eps);
    static bool createParamParserC(VescInterface *vesc, QString filename);
    static uint32_t crc32c(uint8_t *data, uint32_t len);
    static bool checkFwCompatibility(VescInterface *vesc);
    Q_INVOKABLE static QVariantList getNetworkAddresses();
    Q_INVOKABLE static void startGnssForegroundService();
    Q_INVOKABLE static void stopGnssForegroundService();

    static void llhToXyz(double lat, double lon, double height, double *x, double *y, double *z);
    static void xyzToLlh(double x, double y, double z, double *lat, double *lon, double *height);
    static void createEnuMatrix(double lat, double lon, double *enuMat);
    static void llhToEnu(const double *iLlh, const double *llh, double *xyz);
    static void enuToLlh(const double *iLlh, const double *xyz, double *llh);

    template <typename QEnum>
    static QString QEnumToQString(const QEnum value)
    {
        return QString(QMetaEnum::fromType<QEnum>().valueToKey(value));
    }

signals:

public slots:
};

#endif // UTILITY_H
