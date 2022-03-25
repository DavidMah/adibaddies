#include <Arduino.h>
#include "chapter.h"

int msPerTick;
int ticksPerChapter;
int chaptersPerEra;

void chapter_setup(int mpt, int tpc, int cpe) {
    msPerTick = mpt;
    ticksPerChapter = tpc;
    chaptersPerEra = cpe;
}

ChapterInfo chapter_read() {
    int ms = millis();

    int ticksTotal = ms / msPerTick;
    int chaptersTotal = ticksTotal / ticksPerChapter;
    int erasTotal = chaptersTotal / chaptersPerEra;

    int tick = ticksTotal % ticksPerChapter;
    int chapter = chaptersTotal % chaptersPerEra;
    int era = erasTotal;

    return ChapterInfo{
        era,
        chapter,
        chaptersPerEra - chapter,
        tick,
        ticksPerChapter - tick,
        ms,
    };
}
