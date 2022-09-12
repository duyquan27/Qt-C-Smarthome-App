#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QProgressBar>

using std::string;
using std::to_string;

/* ----------- Mode toggle -------------- */
QString OnToggle = "background-color:#8624db;"
                   "border-radius:10px;";

QString OffToggle = "background-color:#333;"
                    "border-radius:10px;";

/* ----------- Mode choose and normal -------------- */
QString modeNormal = "background-color:#e5e5e5;"
                     "color: #000;"
                     "border-radius:9px;";
QString modeChoose = "background-color:#A7CFD7;"
                     "color: #fff;"
                     "border-radius:9px;";

/* --------------- Mode Dashboard ------------ */
QString onDash = "background-color: #9FC899;"
                 "border-radius: 12px;"
                 "border: 1px solid #000;";
QString offDash = "background-color: #FF9AA2;"
                  "border-radius: 12px;"
                  "border: 1px solid #000;";

/* ---------------- Mode selection dashboard ---------------- */
QString selectModeFr = "background-color: #8624db;"
                       "border-radius: 20px";
QString notSelectModeFr = "background-color: #fff;"
                          "border-radius: 20px";
QString selectModeBtn = "border: none;"
                        "background-color: transparent;"
                        "color: #fff;";
QString notSelectModeBtn = "border: none;"
                           "background-color: transparent;"
                           "color: #000;";

int valueChannel = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Time
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(realtime()));
    timer->start(1000);
    // Set widget
    ui->stackedWidget->setCurrentIndex(1);
    // Toggle
    ui->btn_light_bed->setCheckable(true);
    ui->btn_fan_bed->setCheckable(true);
    ui->btn_air_bed->setCheckable(true);
    ui->btn_light_kit->setCheckable(true);
    ui->btn_fan_kit->setCheckable(true);
    ui->btn_timer_kit->setCheckable(true);
    ui->btn_fan_living->setCheckable(true);
    ui->btn_light_living->setCheckable(true);
    ui->btn_air_living->setCheckable(true);
    ui->btn_on_tivi->setCheckable(true);
    ui->btn_clock->setCheckable(true);
    ui->btn_oven_kit->setCheckable(true);
    ui->btn_dash_living->setCheckable(true);
    ui->btn_re_kit->setCheckable(true);
    ui->btn_dash_bed->setCheckable(true);
    ui->btn_dash_kit->setCheckable(true);
    ui->btn_master_dash->setCheckable(true);
    ui->btn_play_music->setCheckable(true);
    ui->btn_vol_music->setCheckable(true);
    // Set volume tivi
    ui->lb_vol_tivi->setText("");
    // Set oven
    ui->lb_temp_kit->setText("");
    // Set master button
    ui->btn_master_dash->setChecked(true);
    // Set selection nav
    ui->stackedWidget->setCurrentIndex(1);
    // dash
    ui->fr_dash->setStyleSheet(selectModeFr);
    ui->btn_dashboard->setStyleSheet(selectModeBtn);
    // living
    ui->fr_living->setStyleSheet(notSelectModeFr);
    ui->btn_living->setStyleSheet(notSelectModeBtn);
    // bed
    ui->fr_bed->setStyleSheet(notSelectModeFr);
    ui->btn_bed->setStyleSheet(notSelectModeBtn);
    // kit
    ui->fr_kit->setStyleSheet(notSelectModeFr);
    ui->btn_kit->setStyleSheet(notSelectModeBtn);
    // on_btn_dashboard_clicked();
    // Set value cb
    for (int i = 0; i < 60; i++)
    {
        if (i < 13)
        {
            ui->cb_timer_h_kit->addItem(QString::number(i));
        }
        if (i < 24)
        {
            ui->cb_timer_h_bed->addItem(QString::number(i));
        }
        ui->cb_timer_m_kit->addItem(QString::number(i));
        ui->cb_timer_m_bed->addItem(QString::number(i));
    }
    // Set hour
    int time = QTime::currentTime().hour();
    if (time > 0 && time < 12)
    {
        ui->lb_img_session->setStyleSheet("image: url(:/img/img/morning.png)");
        ui->lb_wish->setText("Good morning !");
        ui->lb_content->setText("Wish you have nice day.");
    }
    else if (time < 18)
    {
        ui->lb_img_session->setStyleSheet("image: url(:/img/img/noon.png)");
        ui->lb_wish->setText("Good afternon !");
        ui->lb_content->setText("How do you feel today?");
    }
    else
    {
        ui->lb_img_session->setStyleSheet("image: url(:/img/img/night.png)");
        ui->lb_wish->setText("Good evening !");
        ui->lb_content->setText("Good night and have nice dream.");
    }
    // Video
    media = new QMediaPlayer(this);
    mp3 = new QMediaPlayer(this);
    video = new QVideoWidget(this);
    // Music
    playMusic(1);
    on_btn_play_music_toggled(false);
    ui->btn_play_music->setChecked(false);
    mp3->pause();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* -------------- Function for dashboard ------------ */

/* --------------- Navigation --------------- */

void MainWindow::on_btn_dashboard_clicked()
{
    int dashboardPage = 1;
    ui->stackedWidget->setCurrentIndex(dashboardPage);
    // dash
    ui->fr_dash->setStyleSheet(selectModeFr);
    ui->btn_dashboard->setStyleSheet(selectModeBtn);
    // living
    ui->fr_living->setStyleSheet(notSelectModeFr);
    ui->btn_living->setStyleSheet(notSelectModeBtn);
    // bed
    ui->fr_bed->setStyleSheet(notSelectModeFr);
    ui->btn_bed->setStyleSheet(notSelectModeBtn);
    // kit
    ui->fr_kit->setStyleSheet(notSelectModeFr);
    ui->btn_kit->setStyleSheet(notSelectModeBtn);
    video->hide();
}

void MainWindow::on_btn_living_clicked()
{
    int livingPage = 2;
    ui->stackedWidget->setCurrentIndex(livingPage);
    // dash
    ui->fr_dash->setStyleSheet(notSelectModeFr);
    ui->btn_dashboard->setStyleSheet(notSelectModeBtn);
    // living
    ui->fr_living->setStyleSheet(selectModeFr);
    ui->btn_living->setStyleSheet(selectModeBtn);
    // bed
    ui->fr_bed->setStyleSheet(notSelectModeFr);
    ui->btn_bed->setStyleSheet(notSelectModeBtn);
    // kit
    ui->fr_kit->setStyleSheet(notSelectModeFr);
    ui->btn_kit->setStyleSheet(notSelectModeBtn);
    video->show();
}

void MainWindow::on_btn_bed_clicked()
{
    int bedPage = 3;
    ui->stackedWidget->setCurrentIndex(bedPage);
    // dash
    ui->fr_dash->setStyleSheet(notSelectModeFr);
    ui->btn_dashboard->setStyleSheet(notSelectModeBtn);
    // living
    ui->fr_living->setStyleSheet(notSelectModeFr);
    ui->btn_living->setStyleSheet(notSelectModeBtn);
    // bed
    ui->fr_bed->setStyleSheet(selectModeFr);
    ui->btn_bed->setStyleSheet(selectModeBtn);
    // kit
    ui->fr_kit->setStyleSheet(notSelectModeFr);
    ui->btn_kit->setStyleSheet(notSelectModeBtn);
    video->hide();
}

void MainWindow::on_btn_kit_clicked()
{
    int kitPage = 0;
    ui->stackedWidget->setCurrentIndex(kitPage);
    // dash
    ui->fr_dash->setStyleSheet(notSelectModeFr);
    ui->btn_dashboard->setStyleSheet(notSelectModeBtn);
    // living
    ui->fr_living->setStyleSheet(notSelectModeFr);
    ui->btn_living->setStyleSheet(notSelectModeBtn);
    // bed
    ui->fr_bed->setStyleSheet(notSelectModeFr);
    ui->btn_bed->setStyleSheet(notSelectModeBtn);
    // kit
    ui->fr_kit->setStyleSheet(selectModeFr);
    ui->btn_kit->setStyleSheet(selectModeBtn);
    video->hide();
}

/* --------------- Master button --------------- */

void MainWindow::on_btn_master_dash_toggled(bool checked)
{
    QString onBtnPower = "border:1px solid #000;"
                         "border-radius:20px;"
                         "background-color: #F3E9A4;";
    QString offBtnPower = "border:1px solid #000;"
                          "border-radius:20px;"
                          "background-color: #fff;";
    if (checked)
    {
        ui->btn_master_dash->setStyleSheet(onBtnPower);
    }
    else
    {
        on_btn_dash_living_toggled(false);
        on_btn_dash_bed_toggled(false);
        on_btn_dash_kit_toggled(false);
        ui->btn_master_dash->setStyleSheet(offBtnPower);
    }
}

/* -------------- Living room ------------ */
void MainWindow::on_btn_dash_living_toggled(bool checked)
{
    if (ui->btn_master_dash->isChecked())
    {
        if (checked)
        {
            onLivingDash();
            // On Fan
            on_btn_fan_living_toggled(true);
            ui->btn_fan_living->setChecked(true);
            // On light
            on_btn_light_living_toggled(true);
            ui->btn_light_living->setChecked(true);
            // On tivi
            on_btn_on_tivi_toggled(true);
            ui->btn_on_tivi->setChecked(true);
            // On air
            on_btn_air_living_toggled(true);
            ui->btn_air_living->setChecked(true);
        }
        else
        {
            offLivingDash();
            // Off Fan
            on_btn_fan_living_toggled(false);
            ui->btn_fan_living->setChecked(false);
            // Off light
            on_btn_light_living_toggled(false);
            ui->btn_light_living->setChecked(false);
            // Off tivi
            on_btn_on_tivi_toggled(false);
            ui->btn_on_tivi->setChecked(false);
            // Off air
            on_btn_air_living_toggled(false);
            ui->btn_air_living->setChecked(false);
        }
    }
    else
    {
        offLivingDash();
        // Off Fan
        on_btn_fan_living_toggled(false);
        ui->btn_fan_living->setChecked(false);
        // Off light
        on_btn_light_living_toggled(false);
        ui->btn_light_living->setChecked(false);
        // Off tivi
        on_btn_on_tivi_toggled(false);
        ui->btn_on_tivi->setChecked(false);
        // Off air
        on_btn_air_living_toggled(false);
        ui->btn_air_living->setChecked(false);
    }
}

void MainWindow::checkOffLivingDash()
{
    bool checkFanLiving = ui->btn_fan_living->isChecked();
    bool checkLightLiving = ui->btn_light_living->isChecked();
    bool checkTiviLiving = ui->btn_on_tivi->isChecked();
    bool checkAirLiving = ui->btn_air_living->isChecked();
    if (!checkFanLiving && !checkLightLiving && !checkTiviLiving && !checkAirLiving)
    {
        offLivingDash();
    }
}

void MainWindow::onLivingDash()
{
    animation = new QPropertyAnimation(ui->btn_dash_living, "geometry");
    animation->setDuration(150);
    animation->setStartValue(ui->btn_dash_living->geometry());
    animation->setEndValue(QRect(36, 62, 16, 16));
    animation->start();
    ui->lb_dash_living->setStyleSheet(OnToggle);
    ui->lb_status_dash_living->setStyleSheet(onDash);
    // ui->btn_dash_living->setChecked(true);
}

void MainWindow::offLivingDash()
{
    animation = new QPropertyAnimation(ui->btn_dash_living, "geometry");
    animation->setDuration(150);
    animation->setStartValue(ui->btn_dash_living->geometry());
    animation->setEndValue(QRect(22, 62, 16, 16));
    animation->start();
    ui->lb_dash_living->setStyleSheet(OffToggle);
    ui->lb_status_dash_living->setStyleSheet(offDash);
    ui->btn_dash_living->setChecked(false);
}

/* -------------- Bed room ------------ */
void MainWindow::on_btn_dash_bed_toggled(bool checked)
{
    if (ui->btn_master_dash->isChecked())
    {
        if (checked)
        {
            onBedDash();
            // On Fan
            on_btn_fan_bed_toggled(true);
            ui->btn_fan_bed->setChecked(true);
            // On light
            on_btn_light_bed_toggled(true);
            ui->btn_light_bed->setChecked(true);
            // On clock
            on_btn_clock_toggled(true);
            ui->btn_clock->setChecked(true);
            // On air
            on_btn_air_bed_toggled(true);
            ui->btn_air_bed->setChecked(true);
        }
        else
        {
            offBedDash();
            // Off Fan
            on_btn_fan_bed_toggled(false);
            ui->btn_fan_bed->setChecked(false);
            // Off light
            on_btn_light_bed_toggled(false);
            ui->btn_light_bed->setChecked(false);
            // Off clock
            on_btn_clock_toggled(false);
            ui->btn_clock->setChecked(false);
            // Off air
            on_btn_air_bed_toggled(false);
            ui->btn_air_bed->setChecked(false);
        }
    }
    else
    {
        offBedDash();
        // Off Fan
        on_btn_fan_bed_toggled(false);
        ui->btn_fan_bed->setChecked(false);
        // Off light
        on_btn_light_bed_toggled(false);
        ui->btn_light_bed->setChecked(false);
        // Off clock
        on_btn_clock_toggled(false);
        ui->btn_clock->setChecked(false);
        // Off air
        on_btn_air_bed_toggled(false);
        ui->btn_air_bed->setChecked(false);
    }
}

void MainWindow::checkOffBedDash()
{
    bool checkFanBed = ui->btn_fan_bed->isChecked();
    bool checkLightBed = ui->btn_light_bed->isChecked();
    bool checkTiviBed = ui->btn_clock->isChecked();
    bool checkAirBed = ui->btn_air_bed->isChecked();
    if (!checkFanBed && !checkLightBed && !checkTiviBed && !checkAirBed)
    {
        offBedDash();
    }
}

void MainWindow::onBedDash()
{
    animation = new QPropertyAnimation(ui->btn_dash_bed, "geometry");
    animation->setDuration(150);
    animation->setStartValue(ui->btn_dash_bed->geometry());
    animation->setEndValue(QRect(36, 62, 16, 16));
    animation->start();
    ui->lb_dash_bed->setStyleSheet(OnToggle);
    ui->lb_status_dash_bed->setStyleSheet(onDash);
    // ui->btn_dash_bed->setChecked(true);
}

void MainWindow::offBedDash()
{
    animation = new QPropertyAnimation(ui->btn_dash_bed, "geometry");
    animation->setDuration(150);
    animation->setStartValue(ui->btn_dash_bed->geometry());
    animation->setEndValue(QRect(22, 62, 16, 16));
    animation->start();
    ui->lb_dash_bed->setStyleSheet(OffToggle);
    ui->lb_status_dash_bed->setStyleSheet(offDash);
    ui->btn_dash_bed->setChecked(false);
}

/* -------------- Kitchen ------------ */
void MainWindow::on_btn_dash_kit_toggled(bool checked)
{
    if (ui->btn_master_dash->isChecked())
    {
        if (checked)
        {
            onKitDash();
            // On light
            on_btn_light_kit_toggled(true);
            ui->btn_light_kit->setChecked(true);
            // On fan
            on_btn_fan_kit_toggled(true);
            ui->btn_fan_kit->setChecked(true);
            // On oven
            on_btn_oven_kit_toggled(true);
            ui->btn_oven_kit->setChecked(true);
            // On re
            on_btn_re_kit_toggled(true);
            ui->btn_re_kit->setChecked(true);
        }
        else
        {
            offKitDash();
            // Off light
            on_btn_light_kit_toggled(false);
            ui->btn_light_kit->setChecked(false);
            // Off fan
            on_btn_fan_kit_toggled(false);
            ui->btn_fan_kit->setChecked(false);
            // Off oven
            on_btn_oven_kit_toggled(false);
            ui->btn_oven_kit->setChecked(false);
            // Off re
            on_btn_re_kit_toggled(false);
            ui->btn_re_kit->setChecked(false);
        }
    }
    else
    {
        offKitDash();
        // Off light
        on_btn_light_kit_toggled(false);
        ui->btn_light_kit->setChecked(false);
        // Off fan
        on_btn_fan_kit_toggled(false);
        ui->btn_fan_kit->setChecked(false);
        // Off oven
        on_btn_oven_kit_toggled(false);
        ui->btn_oven_kit->setChecked(false);
        // Off re
        on_btn_re_kit_toggled(false);
        ui->btn_re_kit->setChecked(false);
    }
}

void MainWindow::checkOffKitDash()
{
    bool checkFanLiving = ui->btn_fan_kit->isChecked();
    bool checkLightLiving = ui->btn_light_kit->isChecked();
    bool checkOvenLiving = ui->btn_oven_kit->isChecked();
    bool checkReLiving = ui->btn_re_kit->isChecked();
    if (!checkFanLiving && !checkLightLiving && !checkOvenLiving && !checkReLiving)
    {
        offKitDash();
    }
}

void MainWindow::onKitDash()
{
    animation = new QPropertyAnimation(ui->btn_dash_kit, "geometry");
    animation->setDuration(150);
    animation->setStartValue(ui->btn_dash_kit->geometry());
    animation->setEndValue(QRect(36, 62, 16, 16));
    animation->start();
    ui->lb_dash_kit->setStyleSheet(OnToggle);
    ui->lb_status_dash_kit->setStyleSheet(onDash);
    // ui->btn_dash_kit->setChecked(true);
}

void MainWindow::offKitDash()
{
    animation = new QPropertyAnimation(ui->btn_dash_kit, "geometry");
    animation->setDuration(150);
    animation->setStartValue(ui->btn_dash_kit->geometry());
    animation->setEndValue(QRect(22, 62, 16, 16));
    animation->start();
    ui->lb_dash_kit->setStyleSheet(OffToggle);
    ui->lb_status_dash_kit->setStyleSheet(offDash);
    ui->btn_dash_kit->setChecked(false);
}

/* --------------- DEVICE KITCHEN ------------ */

void MainWindow::on_btn_light_kit_toggled(bool checked)
{
    animation = new QPropertyAnimation(ui->btn_light_kit, "geometry");
    animation->setDuration(150);
    if (ui->btn_master_dash->isChecked())
    {
        if (checked)
        {
            animation->setStartValue(ui->btn_light_kit->geometry());
            animation->setEndValue(QRect(96, 212, 16, 16));
            animation->start();
            ui->lb_light_kit->setStyleSheet(OnToggle);
            ui->lb_img_light_kit->setStyleSheet("image: url(:/img/img/lamp_on.png);");
            onKitDash();
        }
        else
        {
            animation->setStartValue(ui->btn_light_kit->geometry());
            animation->setEndValue(QRect(82, 212, 16, 16));
            animation->start();
            ui->lb_light_kit->setStyleSheet(OffToggle);
            ui->lb_img_light_kit->setStyleSheet("image: url(:/img/img/lamp_off.png);");
            checkOffKitDash();
        }
    }
    else
    {
        animation->setStartValue(ui->btn_light_kit->geometry());
        animation->setEndValue(QRect(82, 212, 16, 16));
        animation->start();
        ui->lb_light_kit->setStyleSheet(OffToggle);
        ui->lb_img_light_kit->setStyleSheet("image: url(:/img/img/lamp_off.png);");
    }
}

QString alertHourKit, alertMinKit;
int check, hour, min, second;
void MainWindow::on_btn_timer_kit_toggled(bool checked)
{
    animation = new QPropertyAnimation(ui->btn_timer_kit, "geometry");
    animation->setDuration(150);
    if (ui->btn_oven_kit->isChecked())
    {
        if (checked)
        {
            animation->setStartValue(ui->btn_timer_kit->geometry());
            animation->setEndValue(QRect(216, 12, 16, 16));
            animation->start();
            ui->lb_timer_kit->setStyleSheet(OnToggle);
            alertHourKit = ui->cb_timer_h_kit->currentText();
            alertMinKit = ui->cb_timer_m_kit->currentText();
            qDebug() << "hour: " << alertHourKit << "   min: " << alertMinKit << Qt::endl;
            check = 1;
            onKitDash();
        }
        else
        {
            animation->setStartValue(ui->btn_timer_kit->geometry());
            animation->setEndValue(QRect(203, 12, 16, 16));
            animation->start();
            ui->lb_timer_kit->setStyleSheet(OffToggle);
            alertHourKit = alertMinKit = "";
            hour = min = second = 0;
            check = 2;
        }
    }
    else
    {
        animation->setStartValue(ui->btn_timer_kit->geometry());
        animation->setEndValue(QRect(203, 12, 16, 16));
        animation->start();
        ui->lb_timer_kit->setStyleSheet(OffToggle);
        alertHourKit = alertMinKit = "";
        hour = min = second = 0;
        check = 2;
    }
    qDebug() << "Check: " << check << Qt::endl;
}

/* --------------- Mode Freeze Refrigerator ------------ */

void MainWindow::on_btn_re_kit_toggled(bool checked)
{
    QString onBtnPower = "border:1px solid #000;"
                         "border-radius:20px;"
                         "background-color: #F3E9A4;";
    QString offBtnPower = "border:1px solid #000;"
                          "border-radius:20px;"
                          "background-color: #fff;";
    if (ui->btn_master_dash->isChecked())
    {
        if (checked)
        {
            ui->btn_re_kit->setStyleSheet(onBtnPower);
            ui->btn_mode1_re_kit->setStyleSheet(modeChoose);
            ui->btn_mode2_re_kit->setStyleSheet(modeNormal);
            ui->btn_mode3_re_kit->setStyleSheet(modeNormal);
            ui->horizontalSlider->setValue(10);
            ui->lb_tempre_kit->setText("10°C");
            onKitDash();
        }
        else
        {
            ui->btn_re_kit->setStyleSheet(offBtnPower);
            ui->btn_mode1_re_kit->setStyleSheet(modeNormal);
            ui->btn_mode2_re_kit->setStyleSheet(modeNormal);
            ui->btn_mode3_re_kit->setStyleSheet(modeNormal);
            ui->lb_tempre_kit->setText("");
            checkOffKitDash();
        }
    }
    else
    {
        ui->btn_re_kit->setStyleSheet(offBtnPower);
        ui->btn_mode1_re_kit->setStyleSheet(modeNormal);
        ui->btn_mode2_re_kit->setStyleSheet(modeNormal);
        ui->btn_mode3_re_kit->setStyleSheet(modeNormal);
    }
}

void MainWindow::on_btn_mode1_re_kit_clicked()
{
    if (ui->btn_re_kit->isChecked())
    {
        ui->btn_mode1_re_kit->setStyleSheet(modeChoose);
        ui->btn_mode2_re_kit->setStyleSheet(modeNormal);
        ui->btn_mode3_re_kit->setStyleSheet(modeNormal);
        ui->horizontalSlider->setValue(10);
        ui->lb_tempre_kit->setText("10°C");
    }
}

void MainWindow::on_btn_mode2_re_kit_clicked()
{
    if (ui->btn_re_kit->isChecked())
    {
        ui->btn_mode1_re_kit->setStyleSheet(modeNormal);
        ui->btn_mode2_re_kit->setStyleSheet(modeChoose);
        ui->btn_mode3_re_kit->setStyleSheet(modeNormal);
        ui->horizontalSlider->setValue(5);
        ui->lb_tempre_kit->setText("5°C");
    }
}

void MainWindow::on_btn_mode3_re_kit_clicked()
{
    if (ui->btn_re_kit->isChecked())
    {
        ui->btn_mode1_re_kit->setStyleSheet(modeNormal);
        ui->btn_mode2_re_kit->setStyleSheet(modeNormal);
        ui->btn_mode3_re_kit->setStyleSheet(modeChoose);
        ui->horizontalSlider->setValue(0);
        ui->lb_tempre_kit->setText("0°C");
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    if (ui->btn_re_kit->isChecked())
    {
        value = ui->horizontalSlider->value();
        if (value == 10)
        {
            on_btn_mode1_re_kit_clicked();
        }
        else if (value == 5)
        {
            on_btn_mode2_re_kit_clicked();
        }
        else if (value == 0)
        {
            on_btn_mode3_re_kit_clicked();
        }
        else
        {
            ui->btn_mode1_re_kit->setStyleSheet(modeNormal);
            ui->btn_mode2_re_kit->setStyleSheet(modeNormal);
            ui->btn_mode3_re_kit->setStyleSheet(modeNormal);
        }
        QString text_value = QStringLiteral("%1°C").arg(value);
        ui->lb_tempre_kit->setText(text_value);
    }
}

/* ----------------- Oven kitchen ---------------------- */

int temperatureKit = 100;
void MainWindow::on_btn_oven_kit_toggled(bool checked)
{
    QString onBtnPower = "border:1px solid #000;"
                         "border-radius:20px;"
                         "background-color: #F3E9A4;";
    QString offBtnPower = "border:1px solid #000;"
                          "border-radius:20px;"
                          "background-color: #fff;";
    if (ui->btn_master_dash->isChecked())
    {
        if (checked)
        {
            ui->btn_oven_kit->setStyleSheet(onBtnPower);
            ui->lb_img_oven_kit->setStyleSheet("image: url(:/img/img/oven_on.png);");
            temperatureKit = 100;
            QString txt = QString::number(temperatureKit) + "°C";
            ui->lb_temp_kit->setText(txt);
        }
        else
        {
            ui->btn_oven_kit->setStyleSheet(offBtnPower);
            ui->lb_img_oven_kit->setStyleSheet("image: url(:/img/img/oven_off.png);");
            ui->lb_temp_kit->setText("");
            on_btn_timer_kit_toggled(false);
            ui->btn_timer_kit->setChecked(false);
            checkOffKitDash();
        }
    }
    else
    {
        ui->btn_oven_kit->setStyleSheet(offBtnPower);
        ui->lb_img_oven_kit->setStyleSheet("image: url(:/img/img/oven_off.png);");
        ui->lb_temp_kit->setText("");
        on_btn_timer_kit_toggled(false);
        ui->btn_timer_kit->setChecked(false);
    }
}

void MainWindow::on_btn_up_temp_kit_clicked()
{
    if (ui->btn_oven_kit->isChecked())
    {
        temperatureKit = (temperatureKit == 950) ? 950 : temperatureKit + 50;
        QString txt = QString::number(temperatureKit) + "°C";
        ui->lb_temp_kit->setText(txt);
    }
}

void MainWindow::on_btn_down_temp_kit_clicked()
{
    if (ui->btn_oven_kit->isChecked())
    {
        temperatureKit = (temperatureKit == 100) ? 100 : temperatureKit - 50;
        QString txt = QString::number(temperatureKit) + "°C";
        ui->lb_temp_kit->setText(txt);
    }
}

/* --------------- Fan kitchen --------------- */
void MainWindow::on_btn_fan_kit_toggled(bool checked)
{
    animation = new QPropertyAnimation(ui->btn_fan_kit, "geometry");
    animation->setDuration(150);
    if (ui->btn_master_dash->isChecked())
    {
        if (checked)
        {
            animation->setStartValue(ui->btn_fan_kit->geometry());
            animation->setEndValue(QRect(186, 42, 16, 16));
            animation->start();
            ui->lb_fan_kit->setStyleSheet(OnToggle);
            ui->lb_img_fan_kit->setStyleSheet("image: url(:/img/img/fan_on1.png);");
            ui->btn_mode1_fan_kit->setStyleSheet(modeChoose);
            ui->btn_mode2_fan_kit->setStyleSheet(modeNormal);
            ui->btn_mode3_fan_kit->setStyleSheet(modeNormal);
            onKitDash();
        }
        else
        {
            animation->setStartValue(ui->btn_fan_kit->geometry());
            animation->setEndValue(QRect(172, 42, 16, 16));
            animation->start();
            ui->lb_fan_kit->setStyleSheet(OffToggle);
            ui->lb_img_fan_kit->setStyleSheet("image: url(:/img/img/fan_off.png);");
            ui->btn_mode1_fan_kit->setStyleSheet(modeNormal);
            ui->btn_mode2_fan_kit->setStyleSheet(modeNormal);
            ui->btn_mode3_fan_kit->setStyleSheet(modeNormal);
            checkOffKitDash();
        }
    }
    else
    {
        animation->setStartValue(ui->btn_fan_kit->geometry());
        animation->setEndValue(QRect(172, 42, 16, 16));
        animation->start();
        ui->lb_fan_kit->setStyleSheet(OffToggle);
        ui->lb_img_fan_kit->setStyleSheet("image: url(:/img/img/fan_off.png);");
        ui->btn_mode1_fan_kit->setStyleSheet(modeNormal);
        ui->btn_mode2_fan_kit->setStyleSheet(modeNormal);
        ui->btn_mode3_fan_kit->setStyleSheet(modeNormal);
    }
}

void MainWindow::on_btn_mode1_fan_kit_clicked()
{
    if (ui->btn_fan_kit->isChecked())
    {
        ui->btn_mode1_fan_kit->setStyleSheet(modeChoose);
        ui->btn_mode2_fan_kit->setStyleSheet(modeNormal);
        ui->btn_mode3_fan_kit->setStyleSheet(modeNormal);
        ui->lb_img_fan_kit->setStyleSheet("image: url(:/img/img/fan_on1.png);");
    }
}

void MainWindow::on_btn_mode2_fan_kit_clicked()
{
    if (ui->btn_fan_kit->isChecked())
    {
        ui->btn_mode1_fan_kit->setStyleSheet(modeNormal);
        ui->btn_mode2_fan_kit->setStyleSheet(modeChoose);
        ui->btn_mode3_fan_kit->setStyleSheet(modeNormal);
        ui->lb_img_fan_kit->setStyleSheet("image: url(:/img/img/fan_on2.png);");
    }
}

void MainWindow::on_btn_mode3_fan_kit_clicked()
{
    if (ui->btn_fan_kit->isChecked())
    {
        ui->btn_mode1_fan_kit->setStyleSheet(modeNormal);
        ui->btn_mode2_fan_kit->setStyleSheet(modeNormal);
        ui->btn_mode3_fan_kit->setStyleSheet(modeChoose);
        ui->lb_img_fan_kit->setStyleSheet("image: url(:/img/img/fan_on3.png);");
    }
}

/* --------------- DEVICE LIVING ------------ */

void MainWindow::on_btn_light_living_toggled(bool checked)
{
    animation = new QPropertyAnimation(ui->btn_light_living, "geometry");
    animation->setDuration(150);
    if (ui->btn_master_dash->isChecked())
    {
        if (checked)
        {
            animation->setStartValue(ui->btn_light_living->geometry());
            animation->setEndValue(QRect(76, 212, 16, 16));
            animation->start();
            ui->lb_light_living->setStyleSheet(OnToggle);
            ui->lb_img_light_living->setStyleSheet("image: url(:/img/img/lamp_on.png);");
            onLivingDash();
        }
        else
        {
            animation->setStartValue(ui->btn_light_living->geometry());
            animation->setEndValue(QRect(62, 212, 16, 16));
            animation->start();
            ui->lb_light_living->setStyleSheet(OffToggle);
            ui->lb_img_light_living->setStyleSheet("image: url(:/img/img/lamp_off.png);");
            checkOffLivingDash();
        }
    }
    else
    {
        animation->setStartValue(ui->btn_light_living->geometry());
        animation->setEndValue(QRect(62, 212, 16, 16));
        animation->start();
        ui->lb_light_living->setStyleSheet(OffToggle);
        ui->lb_img_light_living->setStyleSheet("image: url(:/img/img/lamp_off.png);");
    }
}

void MainWindow::on_btn_air_living_toggled(bool checked)
{
    animation = new QPropertyAnimation(ui->btn_air_living, "geometry");
    animation->setDuration(150);
    if (ui->btn_master_dash->isChecked())
    {
        if (checked)
        {
            animation->setStartValue(ui->btn_air_living->geometry());
            animation->setEndValue(QRect(804, 20, 16, 16));
            animation->start();
            ui->lb_air_living->setStyleSheet(OnToggle);
            onLivingDash();
        }
        else
        {
            animation->setStartValue(ui->btn_air_living->geometry());
            animation->setEndValue(QRect(791, 20, 16, 16));
            animation->start();
            ui->lb_air_living->setStyleSheet(OffToggle);
            checkOffLivingDash();
        }
    }
    else
    {
        animation->setStartValue(ui->btn_air_living->geometry());
        animation->setEndValue(QRect(791, 20, 16, 16));
        animation->start();
        ui->lb_air_living->setStyleSheet(OffToggle);
    }
}

/* -------------------- Volume tivi -------------------- */
int volTivi = 15;
void MainWindow::on_btn_on_tivi_toggled(bool checked)
{
    QString onBtnPower = "border:1px solid #000;"
                         "border-radius:14px;"
                         "background-color: #F3E9A4;";
    QString offBtnPower = "border:1px solid #000;"
                          "border-radius:14px;"
                          "background-color: #fff;";
    if (ui->btn_master_dash->isChecked())
    {
        if (checked)
        {
            ui->btn_on_tivi->setStyleSheet(onBtnPower);
            ui->lb_vol_tivi->setText(QString::number(volTivi));
            playVideo(qApp->applicationDirPath() + "/../../project/video/Video1.mpg");
            media->setVolume(volTivi);
            onLivingDash();
        }
        else
        {
            ui->btn_on_tivi->setStyleSheet(offBtnPower);
            ui->lb_vol_tivi->setText("");
            checkOffLivingDash();
            media->stop();
            video->hide();
        }
    }
    else
    {
        ui->btn_on_tivi->setStyleSheet(offBtnPower);
        ui->lb_vol_tivi->setText("");
        media->stop();
        video->hide();
    }
}

void MainWindow::on_btn_up_voltivi_clicked()
{
    if (ui->btn_on_tivi->isChecked())
    {
        volTivi = (volTivi == 100) ? 100 : volTivi + 1;
        ui->lb_vol_tivi->setText(QString::number(volTivi));
        media->setVolume(volTivi);
    }
}

void MainWindow::on_btn_down_voltivi_clicked()
{
    if (ui->btn_on_tivi->isChecked())
    {
        volTivi = (volTivi == 0) ? 0 : volTivi - 1;
        ui->lb_vol_tivi->setText(QString::number(volTivi));
        media->setVolume(volTivi);
    }
}

/* --------------------- Select channel ------------------- */

void MainWindow::on_lb_nextchannel_living_clicked()
{
    QString path1 = qApp->applicationDirPath() + "/../../project/video/Video1.mpg";
    QString path2 = qApp->applicationDirPath() + "/../../project/video/Video2.mpg";
    QString path3 = qApp->applicationDirPath() + "/../../project/video/Video3.mpg";
    valueChannel = (valueChannel == 3) ? 1 : valueChannel + 1;
    if (valueChannel == 1)
    {
        playVideo(path1);
    }
    else if (valueChannel == 2)
    {
        playVideo(path2);
    }
    else if (valueChannel == 3)
    {
        playVideo(path3);
    }
}

void MainWindow::on_lb_prechannel_living_clicked()
{
    QString path1 = qApp->applicationDirPath() + "/../../project/video/Video1.mpg";
    QString path2 = qApp->applicationDirPath() + "/../../project/video/Video2.mpg";
    QString path3 = qApp->applicationDirPath() + "/../../project/video/Video3.mpg";
    valueChannel = (valueChannel == 1) ? 3 : valueChannel - 1;
    if (valueChannel == 1)
    {
        playVideo(path1);
    }
    else if (valueChannel == 2)
    {
        playVideo(path2);
    }
    else if (valueChannel == 3)
    {
        playVideo(path3);
    }
}

/* --------------- Fan living --------------- */

void MainWindow::on_btn_fan_living_toggled(bool checked)
{
    animation = new QPropertyAnimation(ui->btn_fan_living, "geometry");
    animation->setDuration(150);
    if (ui->btn_master_dash->isChecked())
    {
        if (checked)
        {
            animation->setStartValue(ui->btn_fan_living->geometry());
            animation->setEndValue(QRect(186, 52, 16, 16));
            animation->start();
            ui->lb_fan_living->setStyleSheet(OnToggle);
            ui->lb_img_fan_living->setStyleSheet("image: url(:/img/img/fan_on1.png);");
            ui->btn_mode1_fan_living->setStyleSheet(modeChoose);
            ui->btn_mode2_fan_living->setStyleSheet(modeNormal);
            ui->btn_mode3_fan_living->setStyleSheet(modeNormal);
            onLivingDash();
        }
        else
        {
            animation->setStartValue(ui->btn_fan_living->geometry());
            animation->setEndValue(QRect(172, 52, 16, 16));
            animation->start();
            ui->lb_fan_living->setStyleSheet(OffToggle);
            ui->lb_img_fan_living->setStyleSheet("image: url(:/img/img/fan_off.png);");
            ui->btn_mode1_fan_living->setStyleSheet(modeNormal);
            ui->btn_mode2_fan_living->setStyleSheet(modeNormal);
            ui->btn_mode3_fan_living->setStyleSheet(modeNormal);
            checkOffLivingDash();
        }
    }
    else
    {
        animation->setStartValue(ui->btn_fan_living->geometry());
        animation->setEndValue(QRect(172, 52, 16, 16));
        animation->start();
        ui->lb_fan_living->setStyleSheet(OffToggle);
        ui->lb_img_fan_living->setStyleSheet("image: url(:/img/img/fan_off.png);");
        ui->btn_mode1_fan_living->setStyleSheet(modeNormal);
        ui->btn_mode2_fan_living->setStyleSheet(modeNormal);
        ui->btn_mode3_fan_living->setStyleSheet(modeNormal);
    }
}

void MainWindow::on_btn_mode1_fan_living_clicked()
{
    if (ui->btn_fan_living->isChecked())
    {
        ui->btn_mode1_fan_living->setStyleSheet(modeChoose);
        ui->btn_mode2_fan_living->setStyleSheet(modeNormal);
        ui->btn_mode3_fan_living->setStyleSheet(modeNormal);
        ui->lb_img_fan_living->setStyleSheet("image: url(:/img/img/fan_on1.png);");
    }
}

void MainWindow::on_btn_mode2_fan_living_clicked()
{
    if (ui->btn_fan_living->isChecked())
    {
        ui->btn_mode1_fan_living->setStyleSheet(modeNormal);
        ui->btn_mode2_fan_living->setStyleSheet(modeChoose);
        ui->btn_mode3_fan_living->setStyleSheet(modeNormal);
        ui->lb_img_fan_living->setStyleSheet("image: url(:/img/img/fan_on2.png);");
    }
}

void MainWindow::on_btn_mode3_fan_living_clicked()
{
    if (ui->btn_fan_living->isChecked())
    {
        ui->btn_mode1_fan_living->setStyleSheet(modeNormal);
        ui->btn_mode2_fan_living->setStyleSheet(modeNormal);
        ui->btn_mode3_fan_living->setStyleSheet(modeChoose);
        ui->lb_img_fan_living->setStyleSheet("image: url(:/img/img/fan_on3.png);");
    }
}

/* --------------- Air conditioner --------------- */

QString STOP_1 = "";
QString STOP_2 = "";
float value = 0;
float progress;
int i = 16;
QString str;

QString MainWindow::returnNewStyle(QString Stop1, QString Stop2)
{
    return "background-color: qconicalgradient(cx:0.5, cy:0.5, angle:90, stop:" + Stop1 + " rgba(255, 85, 0, 0), stop:" + Stop2 + " rgba(85, 0, 255, 255));border-radius:42px";
}

void MainWindow::on_btn_up_air_living_clicked()
{
    if (ui->btn_air_living->isChecked())
    {
        value = (value > 100) ? 100 : (value + 6.67 > 100) ? 100
                                                           : value + 6.67;
        progress = (100 - value) / 100.0;
        qDebug() << "INC: " << progress << Qt::endl;
        STOP_1 = QString::number(progress - 0.001);
        STOP_2 = QString::number(progress);
        ui->fr_per_air_living->setStyleSheet(returnNewStyle(STOP_1, STOP_2));
        i = (i == 30) ? 30 : i + 1;
        str = QString::number(i);
        ui->lb_per_air_living->setText(str + "°C");
    }
}

void MainWindow::on_btn_down_air_living_clicked()
{
    if (ui->btn_air_living->isChecked())
    {
        value = (value < 0) ? 0 : (value - 6.67 < 0) ? 0
                                                     : value - 6.67;
        progress = (100 - value) / 100.0;
        qDebug() << "DEC: " << progress << Qt::endl;
        STOP_1 = QString::number(progress - 0.001);
        STOP_2 = QString::number(progress);
        ui->fr_per_air_living->setStyleSheet(returnNewStyle(STOP_1, STOP_2));
        i = (i == 16) ? 16 : i - 1;
        str = QString::number(i);
        ui->lb_per_air_living->setText(str + "°C");
    }
}

/* --------------- DEVICE BED ------------ */

QString alertHourBed, alertMinBed;
int val = 0, count = 1;
void MainWindow::on_btn_clock_toggled(bool checked)
{
    QString onBtnPower = "border:1px solid #000;"
                         "border-radius:20px;"
                         "background-color: #F3E9A4;";
    QString offBtnPower = "border:1px solid #000;"
                          "border-radius:20px;"
                          "background-color: #fff;";
    if (ui->btn_master_dash->isChecked())
    {
        if (checked)
        {
            ui->btn_clock->setStyleSheet(onBtnPower);
            alertHourBed = ui->cb_timer_h_bed->currentText();
            alertMinBed = ui->cb_timer_m_bed->currentText();
            qDebug() << "hour: " << alertHourBed << "   min: " << alertMinBed << Qt::endl;
            bool ok;
            if (alertHourBed.toInt(&ok) < 10)
            {
                alertHourBed = "0" + alertHourBed;
            }
            if (alertMinBed.toInt(&ok) < 10)
            {
                alertMinBed = "0" + alertMinBed;
            }
            val = 0;
            count = 1;
            onBedDash();
        }
        else
        {
            ui->btn_clock->setStyleSheet(offBtnPower);
            ui->lb_alert_bed->setStyleSheet(offDash);
            alertHourBed = alertMinBed = "";
            checkOffBedDash();
        }
    }
    else
    {
        ui->btn_clock->setStyleSheet(offBtnPower);
    }
}

/* --------------- Fan bed --------------- */

void MainWindow::on_btn_fan_bed_toggled(bool checked)
{
    animation = new QPropertyAnimation(ui->btn_fan_bed, "geometry");
    animation->setDuration(150);
    if (ui->btn_master_dash->isChecked())
    {
        if (checked)
        {
            animation->setStartValue(ui->btn_fan_bed->geometry());
            animation->setEndValue(QRect(186, 20, 16, 16));
            animation->start();
            ui->lb_fan_bed->setStyleSheet(OnToggle);
            ui->lb_img_fan_bed->setStyleSheet("image: url(:/img/img/fan_on1.png);");
            ui->btn_mode1_fan_bed->setStyleSheet(modeChoose);
            ui->btn_mode2_fan_bed->setStyleSheet(modeNormal);
            ui->btn_mode3_fan_bed->setStyleSheet(modeNormal);
            onBedDash();
        }
        else
        {
            animation->setStartValue(ui->btn_fan_bed->geometry());
            animation->setEndValue(QRect(172, 20, 16, 16));
            animation->start();
            ui->lb_fan_bed->setStyleSheet(OffToggle);
            ui->lb_img_fan_bed->setStyleSheet("image: url(:/img/img/fan_off.png);");
            ui->btn_mode1_fan_bed->setStyleSheet(modeNormal);
            ui->btn_mode2_fan_bed->setStyleSheet(modeNormal);
            ui->btn_mode3_fan_bed->setStyleSheet(modeNormal);
            checkOffBedDash();
        }
    }
    else
    {
        animation->setStartValue(ui->btn_fan_bed->geometry());
        animation->setEndValue(QRect(172, 20, 16, 16));
        animation->start();
        ui->lb_fan_bed->setStyleSheet(OffToggle);
        ui->lb_img_fan_bed->setStyleSheet("image: url(:/img/img/fan_off.png);");
        ui->btn_mode1_fan_bed->setStyleSheet(modeNormal);
        ui->btn_mode2_fan_bed->setStyleSheet(modeNormal);
        ui->btn_mode3_fan_bed->setStyleSheet(modeNormal);
    }
}

void MainWindow::on_btn_mode1_fan_bed_clicked()
{
    if (ui->btn_fan_bed->isChecked())
    {
        ui->btn_mode1_fan_bed->setStyleSheet(modeChoose);
        ui->btn_mode2_fan_bed->setStyleSheet(modeNormal);
        ui->btn_mode3_fan_bed->setStyleSheet(modeNormal);
        ui->lb_img_fan_bed->setStyleSheet("image: url(:/img/img/fan_on1.png);");
    }
}

void MainWindow::on_btn_mode2_fan_bed_clicked()
{
    if (ui->btn_fan_bed->isChecked())
    {
        ui->btn_mode1_fan_bed->setStyleSheet(modeNormal);
        ui->btn_mode2_fan_bed->setStyleSheet(modeChoose);
        ui->btn_mode3_fan_bed->setStyleSheet(modeNormal);
        ui->lb_img_fan_bed->setStyleSheet("image: url(:/img/img/fan_on2.png);");
    }
}

void MainWindow::on_btn_mode3_fan_bed_clicked()
{
    if (ui->btn_fan_bed->isChecked())
    {
        ui->btn_mode1_fan_bed->setStyleSheet(modeNormal);
        ui->btn_mode2_fan_bed->setStyleSheet(modeNormal);
        ui->btn_mode3_fan_bed->setStyleSheet(modeChoose);
        ui->lb_img_fan_bed->setStyleSheet("image: url(:/img/img/fan_on3.png);");
    }
}

/* --------------- Mode Light Bed --------------- */

void MainWindow::on_btn_light_bed_toggled(bool checked)
{
    animation = new QPropertyAnimation(ui->btn_light_bed, "geometry");
    animation->setDuration(150);
    if (ui->btn_master_dash->isChecked())
    {
        if (checked)
        {
            animation->setStartValue(ui->btn_light_bed->geometry());
            animation->setEndValue(QRect(97, 202, 16, 16));
            animation->start();
            ui->lb_light_bed->setStyleSheet(OnToggle);
            ui->lb_img_light_bed->setStyleSheet("image: url(:/img/img/lamp_on.png);");
            onBedDash();
        }
        else
        {
            animation->setStartValue(ui->btn_light_bed->geometry());
            animation->setEndValue(QRect(82, 202, 16, 16));
            animation->start();
            ui->lb_light_bed->setStyleSheet(OffToggle);
            ui->lb_img_light_bed->setStyleSheet("image: url(:/img/img/lamp_off.png);");
            checkOffBedDash();
        }
    }
    else
    {
        animation->setStartValue(ui->btn_light_bed->geometry());
        animation->setEndValue(QRect(82, 202, 16, 16));
        animation->start();
        ui->lb_light_bed->setStyleSheet(OffToggle);
        ui->lb_img_light_bed->setStyleSheet("image: url(:/img/img/lamp_off.png);");
    }
}

void MainWindow::on_btn_light_bed_ye_clicked()
{
    if (ui->btn_light_bed->isChecked())
    {
        ui->lb_img_light_bed->setStyleSheet("image: url(:/img/img/lamp_on.png);");
    }
}

void MainWindow::on_btn_light_bed_bl_clicked()
{
    if (ui->btn_light_bed->isChecked())
    {
        ui->lb_img_light_bed->setStyleSheet("image: url(:/img/img/lamp_on_blue.png);");
    }
}

void MainWindow::on_btn_light_bed_or_clicked()
{
    if (ui->btn_light_bed->isChecked())
    {
        ui->lb_img_light_bed->setStyleSheet("image: url(:/img/img/lamp_on_orange.png);");
    }
}

void MainWindow::on_btn_light_bed_pi_clicked()
{
    if (ui->btn_light_bed->isChecked())
    {
        ui->lb_img_light_bed->setStyleSheet("image: url(:/img/img/lamp_on_pink.png);");
    }
}

/* --------------- Air conditioner --------------- */

void MainWindow::on_btn_air_bed_toggled(bool checked)
{
    animation = new QPropertyAnimation(ui->btn_air_bed, "geometry");
    animation->setDuration(150);
    if (ui->btn_master_dash->isChecked())
    {
        if (checked)
        {
            animation->setStartValue(ui->btn_air_bed->geometry());
            animation->setEndValue(QRect(804, 20, 16, 16));
            animation->start();
            ui->lb_air_bed->setStyleSheet(OnToggle);
            onBedDash();
        }
        else
        {
            animation->setStartValue(ui->btn_air_bed->geometry());
            animation->setEndValue(QRect(790, 20, 16, 16));
            animation->start();
            ui->lb_air_bed->setStyleSheet(OffToggle);
            checkOffBedDash();
        }
    }
    else
    {
        animation->setStartValue(ui->btn_air_bed->geometry());
        animation->setEndValue(QRect(790, 20, 16, 16));
        animation->start();
        ui->lb_air_bed->setStyleSheet(OffToggle);
    }
}

QString STOP_11 = "";
QString STOP_22 = "";
int value1 = 0;
float progress1;
int i1 = 16;
QString str1 = "";

void MainWindow::on_btn_up_air_bed_clicked()
{
    if (ui->btn_air_bed->isChecked())
    {
        value1 = (value1 > 100) ? 100 : (value1 + 6.67 > 100) ? 100
                                                              : value1 + 6.67;
        progress1 = (100 - value1) / 100.0;
        qDebug() << "INC: " << progress1 << Qt::endl;
        STOP_11 = QString::number(progress1 - 0.001);
        STOP_22 = QString::number(progress1);
        ui->fr_per_air_bed->setStyleSheet(returnNewStyle(STOP_11, STOP_22));
        i1 = (i1 == 30) ? 30 : i1 + 1;
        str = QString::number(i1);
        ui->lb_per_air_bed->setText(str + "°C");
    }
}

void MainWindow::on_btn_down_air_bed_clicked()
{
    if (ui->btn_air_bed->isChecked())
    {
        value1 = (value1 < 0) ? 0 : (value1 - 6.67 < 0) ? 0
                                                        : value1 - 6.67;
        progress1 = (100 - value1) / 100.0;
        qDebug() << "DEC: " << progress1 << Qt::endl;
        STOP_11 = QString::number(progress1 - 0.001);
        STOP_22 = QString::number(progress1);
        qDebug() << "Stop 1: " << STOP_11 << Qt::endl;
        qDebug() << "Stop 2: " << STOP_22 << Qt::endl;
        ui->fr_per_air_bed->setStyleSheet(returnNewStyle(STOP_11, STOP_22));
        i1 = (i1 == 16) ? 16 : i1 - 1;
        str1 = QString::number(i1);
        ui->lb_per_air_bed->setText(str1 + "°C");
    }
}

/* ------------------ Play video ----------------------- */

void MainWindow::playVideo(QString path)
{
    qDebug() << "Video path : " << path;
    media->setVideoOutput(video);
    media->setMedia(QUrl::fromLocalFile(path));
    video->setGeometry(661, 142, 294, 161);
    if (ui->stackedWidget->currentIndex() == 2)
    {
        video->show();
    }
    else
    {
        video->hide();
    }
    media->play();
    qDebug() << media->errorString();
}

/* ------------------ Real time clock ----------------------- */

void MainWindow::realtime()
{

    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->lb_time->setText(time_text);
    QDate date = QDate::currentDate();
    QString date_text = date.toString("ddd, MMMM d yyyy");
    ui->lb_date->setText(date_text);
    if (ui->btn_clock->isChecked())
    {
        QString alertBed = alertHourBed + " : " + alertMinBed + " : 00";
        qDebug() << "Time alert: " << alertBed << Qt::endl;
        if (time_text == alertBed)
        {
            val = 1;
        }
        if (val)
        {
            if (count)
            {
                ui->lb_alert_bed->setStyleSheet(onDash);
                count = 0;
            }
            else
            {
                ui->lb_alert_bed->setStyleSheet(offDash);
                count = 1;
            }
        }
    }
    if (ui->btn_timer_kit->isChecked())
    {
        if (check)
        {
            bool ok;
            hour = alertHourKit.toInt(&ok);
            min = alertMinKit.toInt(&ok);
            second = hour * 3600 + min * 60;
            qDebug() << "Second: " << second << Qt::endl;
            check = 0;
        }
        else if (check == 0)
        {
            second--;
            qDebug() << "Second: " << second << Qt::endl;
            if (second == 0)
            {
                on_btn_timer_kit_toggled(false);
                ui->btn_timer_kit->setChecked(false);
                on_btn_oven_kit_toggled(false);
                ui->btn_oven_kit->setChecked(false);
                check = 2;
                // Kiem tra lai
            }
        }
    }
    qDebug() << "Time: " << time_text << Qt::endl;
}

/* ------------------- Play music ------------------------ */

int valueMusic = 1;

void MainWindow::playMusic(int value)
{
    QString path1 = qApp->applicationDirPath() + "/../../project/music/ccby.mp3";
    QString path2 = qApp->applicationDirPath() + "/../../project/music/ttllndce.mp3";
    QString path3 = qApp->applicationDirPath() + "/../../project/music/yd.mp3";
    QString path, nameSong;
    if (value == 1)
    {
        path = path1;
        nameSong = "Chia cách bình yên - Quốc Thiên";
        ui->lb_name_song->setGeometry(QRect(131, 50, 241, 21));
    }
    else if (value == 2)
    {
        path = path2;
        nameSong = "Tháng tư là lời nói dối của em - Hà Anh Tuấn";
        ui->lb_name_song->setGeometry(QRect(110, 50, 241, 21));
    }
    else if (value == 3)
    {
        path = path3;
        nameSong = "Yếu đuối - Hoàng Dũng";
        ui->lb_name_song->setGeometry(QRect(155, 50, 241, 21));
    }
    qDebug() << "Video path : " << path;
    mp3->setMedia(QUrl::fromLocalFile(path));
    mp3->play();
    ui->lb_name_song->setText(nameSong);
    on_btn_play_music_toggled(true);
    ui->btn_play_music->setChecked(true);
    mp3->setVolume(ui->slider_vol_music->value());
    qDebug() << media->errorString();
}

void MainWindow::on_btn_play_music_toggled(bool checked)
{
    QString styleIconPlay = "qproperty-icon: url(:/icon/icon/play.svg);";
    QString styleIconPause = "qproperty-icon: url(:/icon/icon/pause.svg);";
    if (checked)
    {
        ui->btn_play_music->setStyleSheet(styleIconPause);
        mp3->play();
        connect(mp3, &QMediaPlayer::positionChanged, [&](qint64 pos)
                {
                ui->progressBar_music->setValue(pos);
                qDebug() << "Pos : " << pos ; });
        connect(mp3, &QMediaPlayer::durationChanged, [&](qint64 dur)
                {
                ui->progressBar_music->setMaximum(dur);
                qDebug() << "Dur : " << dur ; });
        connect(mp3, &QMediaPlayer::positionChanged, this, [&]()
                { setTimeLabel(); });
    }
    else
    {
        ui->btn_play_music->setStyleSheet(styleIconPlay);
        mp3->pause();
    }
}

void MainWindow::on_btn_next_music_clicked()
{
    valueMusic = (valueMusic == 3) ? 1 : valueMusic + 1;
    playMusic(valueMusic);
}

void MainWindow::on_btn_pre_music_clicked()
{
    valueMusic = (valueMusic == 1) ? 3 : valueMusic - 1;
    playMusic(valueMusic);
}

void MainWindow::setTimeLabel()
{
    // convert duration into HH:MM:SS format and set the lable
    string timeLbl;
    long milli = mp3->position();
    long min = milli / 60000;
    milli = milli - 60000 * min;
    long sec = milli / 1000;

    if (min > 9)
    {
        timeLbl += to_string(min) + ":";
    }
    else
    {
        timeLbl += "0" + to_string(min) + ":";
    }
    if (sec > 9)
    {
        timeLbl += to_string(sec);
    }
    else
    {
        timeLbl += "0" + to_string(sec);
    }
    ui->lb_time_music->setText(QString::fromStdString(timeLbl));
}

void MainWindow::on_btn_vol_music_toggled(bool checked)
{

    QString styleIconMute = "qproperty-icon: url(:/icon/icon/volume-x.svg);";
    QString styleIconMax = "qproperty-icon: url(:/icon/icon/volume-2.svg);";
    if (checked)
    {
        ui->btn_vol_music->setStyleSheet(styleIconMute);
        mp3->setVolume(0);
    }
    else
    {
        ui->btn_vol_music->setStyleSheet(styleIconMax);
        mp3->setVolume(ui->slider_vol_music->value());
    }
}

void MainWindow::on_slider_vol_music_valueChanged(int value)
{
    QString styleIconMute = "qproperty-icon: url(:/icon/icon/volume-x.svg);";
    QString styleIconMax = "qproperty-icon: url(:/icon/icon/volume-2.svg);";
    QString styleIconHalfVol = "qproperty-icon: url(:/icon/icon/volume-1.svg);";
    QString styleIconNoVol = "qproperty-icon: url(:/icon/icon/volume.svg);";
    value = ui->slider_vol_music->value();
    if (value >= 100)
    {
        ui->btn_vol_music->setStyleSheet(styleIconMax);
    }
    else if (value > 50)
    {
        ui->btn_vol_music->setStyleSheet(styleIconHalfVol);
    }
    else if (value > 0)
    {
        ui->btn_vol_music->setStyleSheet(styleIconNoVol);
    }
    else
    {
        ui->btn_vol_music->setStyleSheet(styleIconMute);
    }
    mp3->setVolume(ui->slider_vol_music->value());
}
