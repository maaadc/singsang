#include <M5Core2.h>
#include <SD.h>
#include <vector>
#include <WiFi.h>

#include "Audio.h"

Audio audio;
// todo: encapsulate global variable

namespace singsang
{

    class CPlayer
    {
    public:
        CPlayer() = default;

        ~CPlayer() = default;

        void begin()
        {
            M5.Axp.SetLed(false);
            M5.Axp.SetSpkEnable(true);

            WiFi.mode(WIFI_OFF);
            delay(100);

            populateMusicFileList();

            audio.setPinout(12, 0, 2);
            audio.setVolume(0);
        }

        void loop()
        {
            audio.loop();
        }

        void populateMusicFileList()
        {
            File musicDir = SD.open("/music");

            bool nextFileFound;
            do
            {
                nextFileFound = false;

                File entry = musicDir.openNextFile();

                if (entry)
                {
                    nextFileFound = true;

                    const bool entryIsFile = (entry.size() > 0);
                    if (entryIsFile)
                    {
                        m_songFiles.push_back(entry.name());
                    }

                    entry.close();
                }
            } while (nextFileFound);

            Serial.print("MusicFileList length: ");
            Serial.println(m_songFiles.size());
        }

        void startNextSong()
        {
            if (m_songFiles.size() == 0)
            {
                return;
            }


            m_activeSongIdx++;
            if (m_activeSongIdx >= m_songFiles.size() || m_activeSongIdx < 0)
            {
                m_activeSongIdx = 0;
            }

            //drawFileBulletBar(60, 10, 200, 10, m_songFiles.size(), m_activeSongIdx);

            if (audio.isRunning())
            {
                audio.stopSong();
            }

            audio.connecttoSD(m_songFiles[m_activeSongIdx]);
        }

        int getVolume() const
        {
            return audio.getVolume();
        }

        void updateVolume(int f_deltaVolume)
        {
            constexpr int minVolume = 0;
            constexpr int maxVolume = 16;

            int newVolume = m_currentVolume + f_deltaVolume;

            if (newVolume < minVolume)
            {
                newVolume = minVolume;
            }
            if (newVolume > maxVolume)
            {
                newVolume = maxVolume;
            }

            m_currentVolume = newVolume;
            audio.setVolume(m_currentVolume);
        }

        void increaseVolume()
        {
            updateVolume(+4);
        }

        void decreaseVolume()
        {
            updateVolume(-4);
        }

    private:
        int m_currentVolume = 0;
        int m_activeSongIdx = -1;
        std::vector<String> m_songFiles = {};
    };

} // namespace singsang