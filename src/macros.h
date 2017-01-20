#ifndef MACROS_H
#define MACROS_H

#include <QQmlEngine>
#include <QObject>

#include "enums.h"

#define POKER_QML_NAMESPACE "com.gamedesire.livepro.poker.qt"
#define POKER_QML_NAMESPACE_ENUMS "Poker.Enums"
#define QML_REGISTER_UNCREATABLE_ENUM(Enum) qmlRegisterUncreatableType<Enum>(POKER_QML_NAMESPACE_ENUMS, 1, 0, #Enum, "C++ only!");
#define QML_REGISTER_UNCREATABLE_TYPE(Type) qmlRegisterUncreatableType<Type>(POKER_QML_NAMESPACE, 1, 0, #Type, "C++ only!");
#define QML_CALL // empty method marker that this signal/slot is called directly from QML

#define ANALYTIC_EVENT_SIGNAL void analyticEvent(AnalyticEventType eventType, const AnalyticParams& params = AnalyticParams());

// Empty method markers for .cpp files
#define STATIC_PUBLIC_METHODS
#define Q_INVOKABLE_METHODS
#define PROTECTED_METHODS
#define PRIVATE_METHODS
#define PROTECTED_SLOTS
#define PUBLIC_METHODS
#define PRIVATE_SLOTS
#define PUBLIC_SLOTS

#define AUTO_Q_PROPERTY(Type, name) \
    protected: \
        Q_PROPERTY (Type name READ name WRITE set_##name NOTIFY name##Changed) \
    \
    private: \
        Type m_##name; \
    \
    public: \
        Type name() const \
        { \
            return m_##name ; \
        } \
    \
    public Q_SLOTS: \
        void set_##name(Type name) \
        { \
            if (m_##name == name) \
                return; \
        \
            m_##name = name; \
            emit name##Changed(m_##name); \
        } \
    \
    Q_SIGNALS: \
        void name##Changed(Type name); \
    \
    private:


#define AUTO_READ_ONLY_Q_PROPERTY(Type, name) \
    protected: \
        Q_PROPERTY (Type name READ name) \
    \
    private: \
        Type m_##name; \
    \
    public: \
        Type name() const \
        { \
            return m_##name ; \
        } \
    \
    private:

#endif // MACROS_H
