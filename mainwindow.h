#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QTimer>
#include <QDateTime>
#include <QVideoWidget>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /* Function Dashboard */
    void onLivingDash();
    void offLivingDash();
    void checkOffLivingDash();
    void onBedDash();
    void offBedDash();
    void checkOffBedDash();
    void onKitDash();
    void offKitDash();
    void checkOffKitDash();
    /* End Function Dashboard */
    void on_btn_light_bed_toggled(bool checked);

    void on_btn_fan_bed_toggled(bool checked);

    void on_btn_air_bed_toggled(bool checked);

    void on_btn_light_kit_toggled(bool checked);

    void on_btn_fan_kit_toggled(bool checked);

    void on_btn_timer_kit_toggled(bool checked);

    void on_btn_fan_living_toggled(bool checked);

    void on_btn_light_living_toggled(bool checked);

    void on_btn_air_living_toggled(bool checked);

    void on_btn_dashboard_clicked();

    void on_btn_living_clicked();

    void on_btn_bed_clicked();

    void on_btn_kit_clicked();

    void on_btn_on_tivi_toggled(bool checked);

    void on_btn_clock_toggled(bool checked);

    void on_btn_up_voltivi_clicked();

    void on_btn_down_voltivi_clicked();

    void on_btn_mode1_fan_living_clicked();

    void on_btn_mode2_fan_living_clicked();

    void on_btn_mode3_fan_living_clicked();

    void on_btn_mode1_fan_bed_clicked();

    void on_btn_mode2_fan_bed_clicked();

    void on_btn_mode3_fan_bed_clicked();

    void on_btn_light_bed_ye_clicked();

    void on_btn_light_bed_bl_clicked();

    void on_btn_light_bed_or_clicked();

    void on_btn_light_bed_pi_clicked();

    void on_btn_mode1_fan_kit_clicked();

    void on_btn_mode2_fan_kit_clicked();

    void on_btn_mode3_fan_kit_clicked();

    void on_btn_mode1_re_kit_clicked();

    void on_btn_mode2_re_kit_clicked();

    void on_btn_mode3_re_kit_clicked();

    void on_btn_oven_kit_toggled(bool checked);

    void on_btn_up_temp_kit_clicked();

    void on_btn_down_temp_kit_clicked();

    void on_btn_dash_living_toggled(bool checked);

    void on_btn_dash_bed_toggled(bool checked);

    void on_btn_dash_kit_toggled(bool checked);

    void on_btn_re_kit_toggled(bool checked);

    void on_btn_master_dash_toggled(bool checked);

    void realtime();

    void on_horizontalSlider_valueChanged(int value);

    void on_btn_up_air_living_clicked();

    void on_btn_down_air_living_clicked();

    QString returnNewStyle(QString Stop1,QString Stop2);

    void on_btn_up_air_bed_clicked();

    void on_btn_down_air_bed_clicked();

    void playVideo(QString path);

    void on_lb_nextchannel_living_clicked();

    void on_lb_prechannel_living_clicked();

    void playMusic(int value);

    void on_btn_play_music_toggled(bool checked);

    void on_btn_next_music_clicked();

    void on_btn_pre_music_clicked();

    void setTimeLabel();


    void on_btn_vol_music_toggled(bool checked);

    void on_slider_vol_music_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QPropertyAnimation *animation;
    QTimer *timer;
    QVideoWidget* video;
    QMediaPlayer* media;
    QMediaPlayer* mp3;
};
#endif // MAINWINDOW_H
