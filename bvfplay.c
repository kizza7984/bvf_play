/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"


//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
FONTCHARACTER filename[] = {'\\','\\','f','l','s','0','\\','o','u','t','p','u','t','.','b','v','f',0}; // Filename SET TO FLS FOR PROD, crd for debug

unsigned int key; // Keypad key pressed

// ------- FILE OPS -------
int file; // File handle
unsigned char md_buf[7]; // Buffer to read first bytes of file to
unsigned char byte;
unsigned char vec_buf[1020];
int bytes_read; // Number of bytes read from file

// ------- FILE INFO -------
// METADATA
unsigned int m_frame_rate;
unsigned int m_frame_count;
unsigned int m_horizontal_resolution;
unsigned int m_vertical_resolution;

// RUNNING
unsigned int line_index = 0;
unsigned int frame_index = 0;
unsigned int start;
unsigned int end;
unsigned int num_vectors;

unsigned int frame_vector_count = 0;

unsigned int i;

unsigned int frame_delay;

int AddIn_main(int isAppli, unsigned short OptionNum)
{
    Bdisp_AllClr_DDVRAM();

    file = Bfile_OpenFile(filename, _OPENMODE_READ);
    
    bytes_read = Bfile_ReadFile(file, &md_buf, 7, -1);
    
    m_frame_rate = (int)md_buf[0];
    m_frame_count = (int)(md_buf[4] << 24 | md_buf[3] << 16 | md_buf[2] << 8 | md_buf[1]);
    m_horizontal_resolution = (int)md_buf[5];
    m_vertical_resolution = (int)md_buf[6];
    free(md_buf);

    frame_delay = 1000 / m_frame_rate;

    while (bytes_read) {
        if (line_index == m_vertical_resolution) {
            frame_index++;
            Bdisp_PutDisp_DD();
            //Sleep(frame_delay - frame_vector_count);
            Bdisp_AllClr_VRAM();
            line_index = 0;
            frame_vector_count = 0;
	//GetKey(&key);
        }
        memset(vec_buf, 0, sizeof vec_buf);
        bytes_read = Bfile_ReadFile(file, &byte, 1, -1);
        num_vectors = (int)byte;
        frame_vector_count += num_vectors;
        if (num_vectors != 0) {
            bytes_read = Bfile_ReadFile(file, &vec_buf, num_vectors*2, -1);
        }
        for (i=0; i < num_vectors*2; i+=2) {
            Bdisp_DrawLineVRAM(vec_buf[i], line_index, vec_buf[i+1], line_index);
        }
        line_index++;
    }

    while(1){
        GetKey(&key);
    }

    return 1;
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

