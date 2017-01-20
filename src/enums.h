#ifndef ENUMS_H
#define ENUMS_H

#include <QVariant>
#include <QString>
#include <QMap>

typedef QMapIterator<QString, QVariant> AnalyticParamsIterator;
typedef QMapIterator<QString, QString> AnalyticEventIterator;
typedef QMap<QString, QVariant> AnalyticParams;
typedef QMap<QString, QString> AnalyticEvent;

class Enums
{
    Q_GADGET

public:
    enum AnalyticEventType
    {
        EventUndefined = 0,
        LoginOptionChosen,
        RegistrationStart,
        RegistrationSuccess,
        DeviceInfo,
        MainLobbyScreen,
        PlayCash,
        StakesChosen,
        EnterLobby,
        EnterTable,
        SitDown,
        AddTable,
        TournamentAction,
        ShopOpen,
        TransactionStart,
        TransactionEnd,
        HandStarted,
        HandEnded,
        HandAction,
        Rebuy,
        ChangeTable,
        TournamentFinish,
        SettingChange,
        OptionUse,
        WindowView,
        SideView,
        CrmView,
        SitOut,
        StandUp,
        CloseTable,
        DailyBonus,
        LocalNotification,
        SocialJoin,
        SocialInvite
    };
    Q_ENUM(AnalyticEventType)

    enum SoundEffect
    {
        SoundEffectCall = 0,
        SoundEffectCheck,
        SoundEffectClick,
        SoundEffectDeal,
        SoundEffectDialog,
        SoundEffectFold,
        SoundEffectGather,
        SoundEffectMoneyMove,
        SoundEffectRaise0,
        SoundEffectRaise1,
        SoundEffectRaise2,
        SoundEffectShuffle,
        SoundEffectSmallClick,
        SoundEffectWinMoney,

        SoundEffectCount
    };
    Q_ENUM(SoundEffect)
};

typedef Enums::AnalyticEventType AnalyticEventType;

#endif // ENUMS_H
