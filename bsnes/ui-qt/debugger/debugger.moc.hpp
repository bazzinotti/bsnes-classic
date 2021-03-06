class Debugger : public Window {
  Q_OBJECT

public:
  QMenuBar *menu;
  QMenu *menu_tools;
  QAction *menu_tools_disassembler;
  QAction *menu_tools_breakpoint;
  QAction *menu_tools_memory;
  QAction *menu_tools_propertiesViewer;
  QMenu *menu_ppu;
  QAction *menu_ppu_vramViewer;
  QAction *menu_ppu_oamViewer;
  QAction *menu_ppu_cgramViewer;
  QMenu *menu_misc;
  QAction *menu_misc_clear;
  QAction *menu_misc_options;

  QHBoxLayout *layout;
  QTextEdit *console;
  QVBoxLayout *controlLayout;
  QHBoxLayout *commandLayout;
  QPushButton *runBreak;
  QPushButton *stepInstruction;
  QCheckBox *stepCPU;
  QCheckBox *stepSMP;
  QCheckBox *traceCPU;
  QCheckBox *traceSMP;
  QCheckBox *traceMask;
  QCheckBox *autobreak;
  QHBoxLayout *frameBreakLayout;
  QCheckBox *frameBreak;
  QSpinBox *frameBreakSpinBox;
  QWidget *spacer;

  QHBoxLayout *AUTicksLayout;
  QLabel *AUTicksLabel;
  QSpinBox *AUTicks;

  unsigned frameBreak_last=0;

  void modifySystemState(unsigned);
  void echo(const char *message);
  void event();
  void frameTick();
  void autoUpdate();
  Debugger();

public slots:
  void setAutoBreak(int i);
  void setFrameBreak(int i);
  void clear();
  void synchronize();

  void toggleRunStatus();
  void stepAction();

private:
  unsigned frameCounter;
};

extern Debugger *debugger;
