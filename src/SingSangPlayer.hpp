#include <M5Core2.h>
#include <driver/i2s.h>
#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

class SingSangPlayer
{
public:
    SingSangPlayer()
    {
        M5.Axp.SetSpkEnable(true);

        m_file = new AudioFileSourceSD();
        m_mp3 = new AudioGeneratorMP3();

        // play on the built-in DAC of the M5stack Core2
        m_out = new AudioOutputI2S(0, 0);
        m_out->SetPinout(12, 0, 2);
        m_out->SetOutputModeMono(true);
        setVolume(0.4);
    }

    ~SingSangPlayer()
    {
    }

    void loopPlay()
    {
        if (m_mp3->isRunning())
        {
            if (!m_mp3->loop())
                m_mp3->stop();
        }
        else
        {
            M5.Lcd.println("Player not running.");
            delay(1000);
        }
    }

    void playMp3(const char *f_filePath)
    {        
        M5.Lcd.println(f_filePath);

        if (m_file->isOpen())
        {
            m_file->close();
        }
        m_file->open(f_filePath);

        m_id3 = new AudioFileSourceID3(m_file);
        m_id3->RegisterMetadataCB(this->MDCallback, (void *)"ID3TAG");

        M5.Lcd.println("play");

        m_mp3->begin(m_id3, m_out);
    }

    void setVolume(float f_gain)
    {
        if (f_gain >= 0.F && f_gain <= 1.F)
        {
            m_out->SetGain(f_gain);
        }
    }

    static void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string)
    {
        (void)cbData;
        M5.Lcd.printf("ID3: %s = '", type);

        if (isUnicode)
        {
            string += 2;
        }

        while (*string)
        {
            char a = *(string++);
            if (isUnicode)
            {
                string++;
            }
            M5.Lcd.printf("%c", a);
        }
        M5.Lcd.printf("'\n");
    }

private:
    AudioGeneratorMP3 *m_mp3;
    AudioFileSourceSD *m_file;
    AudioOutputI2S *m_out;
    AudioFileSourceID3 *m_id3;
};

SingSangPlayer singsang;