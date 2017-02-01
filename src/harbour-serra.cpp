/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QGuiApplication>
#include <QScopedPointer>
#include <QQuickView>
#include <QQmlContext>

#include <QFile>

#include "commandsparser.h"
#include "googlesearchhelper.h"
#include "recorder.h"
#include "scriptrunner.h"
#include "settingswrapper.h"
#include "weatherhelper.h"
#include "yandexsearchhelper.h"
#include "yandexspeechkithelper.h"


int main(int argc, char *argv[]) {
    QFile localeFile("/var/lib/environment/nemo/locale.conf");
    QString localeName = "";
    if (localeFile.open(QIODevice::ReadOnly)) {
        QStringList lines = QString(localeFile.readAll()).split("LANG=");
        localeName = lines[1].left(5).replace("_", "-");
        if (localeName.startsWith("en-")) localeName = localeName.left(3) + "US";
        localeFile.close();
    }
    qDebug() << localeName;

    QScopedPointer<QGuiApplication> application(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    QScopedPointer<CommandsParser> commandsParser(new CommandsParser(view.data()));
    QScopedPointer<GoogleSearchHelper> googleSearchHelper(new GoogleSearchHelper(view.data()));
    QScopedPointer<Recorder> recorder(new Recorder(view.data()));
    QScopedPointer<ScriptRunner> scriptRunner(new ScriptRunner(view.data()));
    QScopedPointer<SettingsWrapper> settings(new SettingsWrapper(view.data()));
    QScopedPointer<WeatherHelper> weatherHelper(new WeatherHelper(view.data()));
    QScopedPointer<YandexSearchHelper> yandexSearchHelper(new YandexSearchHelper(view.data()));
    QScopedPointer<YandexSpeechKitHelper> yandexSpeechKitHelper(new YandexSpeechKitHelper(view.data()));

    view->rootContext()->setContextProperty("commandsParser", commandsParser.data());
    view->rootContext()->setContextProperty("googleSearchHelper", googleSearchHelper.data());
    view->rootContext()->setContextProperty("recorder", recorder.data());
    view->rootContext()->setContextProperty("scriptRunner", scriptRunner.data());
    view->rootContext()->setContextProperty("settings", settings.data());
    view->rootContext()->setContextProperty("weatherHelper", weatherHelper.data());
    view->rootContext()->setContextProperty("yandexSearchHelper", yandexSearchHelper.data());
    view->rootContext()->setContextProperty("yandexSpeechKitHelper", yandexSpeechKitHelper.data());
    view->rootContext()->setContextProperty("localeString", localeName);

    view->setSource(SailfishApp::pathTo("qml/harbour-serra.qml"));
    view->show();

    return application->exec();
}
