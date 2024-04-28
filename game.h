#include <U8g2lib.h>
#include "funks.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C tela(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);


// Variáveis do cronômetro
unsigned long start_time = 0;
float tempo_corrente = 0;
char buffer[10];

unsigned char setas[4] = {0x0074,0x0075,0x0076,0x0077}; //↓←→↑
unsigned char setas_formado[4] = {' ',' ',' ',' '};
unsigned char setas_jogador[4] = {' ',' ',' ',' '};
String score_time[3] = {"00.0","00.0","00.0"};
unsigned int pos_score = 2;
int pontos = 0;
int pos = 0;
bool new_frame = true;
int igualdade = 0;

// void setup_game_variaveis()
// {
//     // Variáveis do cronômetro
//     start_time = 0;
//     tempo_corrente = 0;
//     buffer[10];
//     String score_time[3] = {"00.0","00.0","00.0"};
//     pos_score = 1;
//     pontos = 0;
//     pos = 0;
//     new_frame = true;
//     igualdade = 0;
// }


bool menu()
{
    bool in_menu = true;
    while (in_menu)
    {
        String botao_lido = read_buttons();   
        if(botao_lido == "b1")
        {
            in_menu = false;
        }
        tela.clearBuffer();
        tela.drawFrame(0,0,128,16);
        tela.setFont(u8g_font_7x14);
        tela.drawStr(2,13,"SpeedSeta!    v0.1");
        tela.setCursor(3,30+0 * 15);
        tela.println("Iniciar jogo <");
        tela.setCursor(0,50);
        tela.print("Um projeto");
        tela.setCursor(0,64);
        tela.print("Randoom Colors!");
        tela.sendBuffer();
    }
    tela.clearDisplay();

    tela.drawStr(10,32,"Iniciando 3");
    tela.sendBuffer();
    delay(500);

    tela.drawStr(10,32,"Iniciando 2");
    tela.sendBuffer();
    delay(500);

    tela.drawStr(10,32,"Iniciando 1");
    tela.sendBuffer();

    delay(random(500,2500));
    tela.clearDisplay();
    tela.drawStr(10,32,"VAI!");
    tela.sendBuffer();
    delay(500);
    new_frame = true;
}

bool speed_seta()
{
    for (size_t i = 0; i < 4; i++)
    {
       setas_formado[i] = setas[random(0,4)];
       setas_jogador[i] = ' ';
    }
    igualdade = 0;
    // pos = 0;
    new_frame = true;
    pontos += 1 ;
    while(igualdade != 4)
    {
        for (size_t i = 0; i < 4; i++)
        {
            if(setas_formado[i] == setas_jogador[i])
            {
                igualdade ++;
            }
        }
        if(igualdade < 4)
        {
            igualdade = 0;
            // if(pos != 4)
            // {
            //     pontos--;
            // }
        }
        if(pos == 4)
        {
            tela.setFont(u8g2_font_open_iconic_all_2x_t);
            if(igualdade != 4)
            {
                tela.drawGlyph(0,20,0x0079);
                tela.sendBuffer();
                
            }
            else//acerto
            {
                tela.drawGlyph(0,20,0x0078);
                tela.sendBuffer();
                for (int i = 0; i < 2; i++) {
                    score_time[i] = score_time[i + 1];
                }

                // Adiciona o novo score na última posição
                score_time[2] = tempo_corrente;
                
                tempo_corrente = 0;
                
            }
            delay(250);
            for (size_t i = 0; i < 4; i++)
            {
                setas_jogador[i] = ' ';
            }
            pos = 0;
            
            new_frame = true;
            // pontos ++;
        }

        if(read_buttons() == "up")
        {
            setas_jogador[pos] = 0x0077;
            pos++;
            new_frame = true;
        }
        else if(read_buttons() == "down")
        {
            setas_jogador[pos] = 0x0074;
            pos++;
            new_frame = true;
        }
        else if(read_buttons() == "left")
        {
            setas_jogador[pos] = 0x0075;
            pos++;
            new_frame = true;
        }
        else if(read_buttons() == "right")
        {
            setas_jogador[pos] = 0x0076;
            pos++;
            new_frame = true;
        }
        else if(read_buttons() == "b2")
        { 
            if(pos > 0)
            {
                pos--;
            }
            setas_jogador[pos] = ' ';
            new_frame = true;
        } 
        if(new_frame == true)
        {
            tela.clearBuffer();
            for (size_t i = 0; i < 4; i++)
            {
                tela.setFont(u8g_font_9x15);
                tela.setCursor(0,64);
                tela.print("T");
                tela.print(String(pontos).c_str());
                tela.print(":");
                tela.print(String((score_time[0].toFloat() + score_time[1].toFloat() + score_time[2].toFloat())/3).c_str());
                // tela.drawStr(0,64,"SPEED:");
                if(i < 3)
                {
                    tela.drawStr(92, 16 + (i*16), String(score_time[i]).c_str());
                }
                tela.setFont(u8g2_font_open_iconic_all_2x_t);
                tela.drawGlyph(16 + (i *16),20,setas_formado[i]);
                tela.drawGlyph(16 + (i *16),40,setas_jogador[i]);
            }
            tela.sendBuffer();
            new_frame = false;
        }
        if (millis() - start_time >= 10) { // A cada segundo
            start_time = millis(); // Reinicia o cronômetro
            // Faz algo a cada segundo
            tempo_corrente+=0.1;
            tela.setFont(u8g_font_9x15);
            dtostrf(tempo_corrente, 6, 1, buffer);
            tela.drawStr(74,64, buffer);
            tela.sendBuffer();
        }
        if(read_buttons() == "b1")
        { 
            setup();
        }   
    }
}