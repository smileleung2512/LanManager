#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QTreeWidget>
#include <QLabel>
#include <QProgressBar>
#include <QSplitter>
#include <QSlider>
#include <QSpinBox>
#include <QTimer>
#include "tcpserver.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    // 按钮点击事件
    void onStartServer();
    void onStopServer();
    void onRefreshSysInfo();
    void onRefreshSoftware();
    void onInstallSoftware();
    void onUninstallSoftware();
    void onSelectAll();
    void onDeselectAll();
    
    // 服务器事件
    void onClientConnected(qintptr clientId);
    void onClientDisconnected(qintptr clientId);
    void onClientInfoUpdated(qintptr clientId);
    void onSysInfoReceived(qintptr clientId, const SystemInfo& info);
    void onSoftwareListReceived(qintptr clientId, const QList<SoftwareInfo>& list);
    void onInstallResult(qintptr clientId, bool success, const QString& message);
    void onUninstallResult(qintptr clientId, bool success, const QString& message);
    void onFileTransferProgress(qintptr clientId, int percent);
    void onLogMessage(const QString& message);
    void onScreenFrameReceived(qintptr clientId, const QByteArray& imageData, qint64 timestamp, const QSize& size);

    // 屏幕监控操作
    void onStartScreenMonitor();
    void onStopScreenMonitor();
    void onReplaySliderChanged(int value);
    void onStartReplay();
    void onStopReplay();
    void onReplayTick();
    
    // 表格选择变化
    void onClientSelectionChanged();
    
private:
    void setupUI();
    void createMenuBar();
    void updateClientList();
    void updateSysInfoDisplay(const SystemInfo& info);
    void updateSoftwareList(const QList<SoftwareInfo>& list);
    QList<qintptr> getSelectedClients();
    void addLog(const QString& message);
    void showScreenFrame(qintptr clientId, int frameIndex);
    
private:
    TcpServer* m_server;
    
    // UI组件
    QTableWidget* m_clientTable;      // 客户端列表
    QTextEdit* m_sysInfoText;         // 系统信息显示
    QTreeWidget* m_softwareTree;      // 软件列表
    QLabel* m_screenPreviewLabel;     // 屏幕预览
    QLabel* m_screenInfoLabel;        // 屏幕状态信息
    QSlider* m_replaySlider;          // 回放滑块
    QSpinBox* m_screenIntervalSpin;   // 抓帧间隔
    QSpinBox* m_screenQualitySpin;    // 图像质量
    QTextEdit* m_logText;             // 日志
    QProgressBar* m_progressBar;      // 进度条
    QLabel* m_statusLabel;            // 状态标签
    
    // 按钮
    QPushButton* m_btnStart;
    QPushButton* m_btnStop;
    QPushButton* m_btnRefreshSysInfo;
    QPushButton* m_btnRefreshSoftware;
    QPushButton* m_btnInstall;
    QPushButton* m_btnUninstall;
    QPushButton* m_btnStartScreen;
    QPushButton* m_btnStopScreen;
    QPushButton* m_btnStartReplay;
    QPushButton* m_btnStopReplay;
    QPushButton* m_btnSelectAll;
    QPushButton* m_btnDeselectAll;
    
    struct ScreenRecord {
        QString filePath;
        qint64 timestamp;
        QSize size;
    };

    // 当前选中的客户端
    qintptr m_currentClient;

    // 屏幕回放定时器
    QTimer* m_replayTimer;

    // 缓存的软件列表
    QMap<qintptr, QList<SoftwareInfo>> m_softwareLists;
    QMap<qintptr, QList<ScreenRecord>> m_screenRecords;
};

#endif // MAINWINDOW_H
