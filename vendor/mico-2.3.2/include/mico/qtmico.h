// -*- c++ -*-
/*
 *  Qt support for MICO
 *  Copyright (C) 1997 Lars Doelle
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Send comments and/or bug reports to:
 *                 mico@informatik.uni-frankfurt.de
 */

#ifndef __mico_qt_h__
#define __mico_qt_h__

/*
 * XXX ugly hack to make QApplication::processNextEvent() and
 * QApplication::quit_now accessible to CApp
 */
#define private protected
#ifdef HAVE_QAPPLICATION_H
#include <qapplication.h>
#else
#include <qapp.h>
#endif
#undef private

#ifdef HAVE_QSOCKETNOTIFIER_H
#include <qsocketnotifier.h>
#else
#include <qsocknot.h>
#endif

#include <qtimer.h>
#include <CORBA.h>

class QTDispatcher; // forward

class CApp : public QApplication {
    Q_OBJECT
    enum State {
	Initial,
	ObjReady,
	ImplReady
    };
    State state;
    QTDispatcher* qtd;

    void doquit();
public:
    CORBA::BOA_var boa;
    CORBA::ORB_var orb;

    CApp(int argc, char *argv[]);
    ~CApp();

    void impl_is_ready (CORBA::ImplementationDef_ptr);
    void deactivate_impl (CORBA::ImplementationDef_ptr);
    void obj_is_ready (CORBA::Object_ptr, CORBA::ImplementationDef_ptr);
    void deactivate_obj (CORBA::Object_ptr);
    void run ();
    void shutdown (CORBA::Boolean wait);

    void processNextEvent (bool b);
};

class FileEvent : public QObject {
    Q_OBJECT
public:
    QSocketNotifier* xid;
    CORBA::DispatcherCallback *cb;
    QTDispatcher* disp;
    CORBA::Dispatcher::Event ev;
    ~FileEvent ();
    FileEvent ();
    FileEvent (QTDispatcher *_disp, CORBA::DispatcherCallback *_cb,
	       int fd,  QSocketNotifier::Type _evq,
	       CORBA::Dispatcher::Event _evc);
private slots:
    void activated (int /*fd*/);
};

class TimerEvent : public QObject {
    Q_OBJECT
public:
    QTimer* xid;
    CORBA::DispatcherCallback *cb;
    QTDispatcher* disp;
    ~TimerEvent ();
    TimerEvent ();
    TimerEvent (QTDispatcher* _disp, CORBA::DispatcherCallback *_cb,
		long tmout);
private slots:
    void timeout();
};

class QTDispatcher : public CORBA::Dispatcher {
    CApp* ctx;

    list<FileEvent*> fevents;
    list<TimerEvent*> tevents;

public:
    QTDispatcher (CApp*);
    virtual ~QTDispatcher ();

    virtual void rd_event (CORBA::DispatcherCallback *, CORBA::Long fd);
    virtual void wr_event (CORBA::DispatcherCallback *, CORBA::Long fd);
    virtual void ex_event (CORBA::DispatcherCallback *, CORBA::Long fd);
    virtual void tm_event (CORBA::DispatcherCallback *, CORBA::ULong tmout);
    virtual void remove (CORBA::DispatcherCallback *, Event);
    virtual void run (CORBA::Boolean infinite = TRUE);
    virtual void move (CORBA::Dispatcher *);
    virtual CORBA::Boolean idle () const;

    void remove (TimerEvent *);
};

#endif // __mico_qt_h__
