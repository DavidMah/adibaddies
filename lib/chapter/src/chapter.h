struct ChapterInfo {
  int era;
  int chapter;
  int chapterInverse;

  int tick;
  int tickInverse;

  int ms;
};

void chapter_setup(int msPerTick, int ticksPerChapter, int chaptersPerEra);

ChapterInfo chapter_read();
