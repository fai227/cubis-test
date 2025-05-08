#include "audio.hpp"

#define RRES_RAYLIB_IMPLEMENTATION
#define RRES_IMPLEMENTATION

#include "raylib.h"
#include "rres.h"
#include "rres-raylib.h"

Music music;
void AudioManager::Init()
{
    InitAudioDevice(); // 音声デバイスの初期化

    // 1. 複数チャンク読み込み（ID=0想定）
    rresResourceMulti multi = rresLoadResourceMulti("res/bgm.rres", 0x07046e04);
    if (multi.count == 0)
    {
        TraceLog(LOG_ERROR, "No BGM resource chunks found.");
        return;
    }

    // 2. 最初のチャンクを展開
    rresResourceChunk chunk = multi.chunks[0];
    if (UnpackResourceChunk(&chunk) != 0)
    {
        TraceLog(LOG_ERROR, "Failed to unpack BGM chunk.");
        rresUnloadResourceMulti(multi);
        return;
    }

    Wave wave = LoadWaveFromResource(chunk);
    Sound sound = LoadSoundFromWave(wave);
    Music music = {
        sound.stream,
        sound.frameCount,
        true,

        2,
        nullptr};
    PlayMusicStream(music);
}

void AudioManager::Update()
{
    UpdateMusicStream(music);
}

void AudioManager::Unload()
{
    CloseAudioDevice(); // 音声デバイスを閉じる
}