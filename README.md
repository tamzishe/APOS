# APOS Music Player

An iPod Nano-inspired music player, built with Qt Widgets. This is **Stage 0** of the APOS project: a desktop prototype of the software, ahead of eventually running on custom embedded hardware.

## About APOS

APOS is a from-scratch embedded music player project, developed in three stages:

- **Stage 0 (current)** — Windows desktop application, built with Qt Widgets and Qt Multimedia. This is where the UI, playback logic, and iPod-style interaction model are designed and refined before touching hardware.
- **Stage 1** — Port for a Raspberry Pi Zero 2 W.

## Features

- Recursively scans a music folder for audio files (`.mp3`, `.flac`, `.wav`, `.m4a`, `.ogg`)
- Reads title, artist, album, and embedded cover art from each file's tags (via Qt Multimedia — no external tag-reading library required)
- Custom list view showing title, artist, and album art per song
- Click a song to play it; click the currently playing song again to open a fullscreen Now Playing view
- Fullscreen Now Playing view with enlarged cover art, title, and artist
- Full keyboard control, modeled to mimic the iPod Nano's click wheel (see below)

## Keyboard Controls

| Key | Action |
|---|---|
| ← | Restart the current song, or skip to the previous song if pressed within the first few seconds |
| → | Skip to the next song |
| ↑ | Move selection up (list view) / Toggle play-pause (Now Playing view) |
| ↓ | Move selection down (list view) / Return to the list (Now Playing view) |
| Enter | Play the selected song |
| + | Increase volume |
| − | Decrease volume |

## Steps for building

coming soon!!