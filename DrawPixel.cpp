
#include "DxLib.h"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){

    SetMainWindowText( "���~�Q�[��" ) ;

	if( ChangeWindowMode(TRUE) != 0 ){
                return 0;
        }
        if( DxLib_Init() != 0 ){
                return 0;
        }
        if( SetDrawScreen( DX_SCREEN_BACK ) != 0 ){
                DxLib_End();
                return 0;
        }
	//�O�����I��
		int kadox_s = 640/2 -210, kadoy_s = (480-420)/2, saizu_s = 140, saizu_n =120, flgu[3][3], i, j,
		 kuro, siro, gure, maru_h, batu_h, bg_h, tflgu = 0, mausux, mausuy, sflgu = 0;

       
        while( 1 ){
                if( ScreenFlip() != 0 ){
                        break;
                }
                if( ProcessMessage() != 0 ){
                        break;
                }
                if( ClearDrawScreen() != 0 ){
                        break;
                }
				SetDrawScreen( DX_SCREEN_BACK ); //�`���𗠉�ʂɐݒ�
				
				for(i = 0; i<3; i++){
					for(j=0; j<3; j++){ 
						flgu[i][j] = 0;
					}}
		 //�t���O�̏�����
				batu_h = LoadGraph( "�摜/batu.png" );
				maru_h = LoadGraph( "�摜/maru.png" );
				bg_h = LoadGraph( "�摜/bg.png" );// �摜�����[�h
      
				kuro = GetColor(0, 0, 0) ;
				gure = GetColor(160, 160, 160) ;// �F�̒l���擾

				while(sflgu == 0){
					if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 ){
						GetMousePoint( &mausux , &mausuy );

						for(i=0; i<3; i++){
							for(j=0; j<3; j++){
								if(mausux >= kadox_s+(saizu_s*j)+((saizu_s-saizu_n)/2) 
									&& mausuy >= kadoy_s+(saizu_s*i)+((saizu_s-saizu_n)/2) 
									&& mausux <= kadox_s+(saizu_s*j)+((saizu_s-saizu_n)/2)+saizu_n 
									&& mausuy <= kadoy_s+(saizu_s*i)+((saizu_s-saizu_n)/2)+saizu_n){
										
										if(tflgu == 0 && flgu[j][i] == 0){
											 tflgu = 1;
											 flgu[j][i] = 1;

										}
										if(tflgu == 1 && flgu[j][i] == 0){
											 tflgu = 0;
											 flgu[j][i] = 2;
										}
								}
							}}
				}//�N���b�N
			
				DrawGraph(0 ,0 , bg_h, FALSE );	
							
				for(i=0; i<3; i++){
					for(j=0; j<3; j++){
						if(flgu[j][i] == 1){
							DrawGraph( kadox_s+(saizu_s*j)+((saizu_s-saizu_n)/2) ,kadoy_s+(saizu_s*i)+((saizu_s-saizu_n)/2), maru_h, FALSE );	
						}
						else if(flgu[j][i] == 2){
							DrawGraph( kadox_s+(saizu_s*j)+((saizu_s-saizu_n)/2) ,kadoy_s+(saizu_s*i)+((saizu_s-saizu_n)/2), batu_h, FALSE  );
						}
						}}

				if(tflgu == 0){
					DrawString( 20 ,40 , "���̔�" ,kuro );
					DrawString( 550 ,40 , "�~�̔�" ,gure);
				}else{
					DrawString(20, 40, "���̔�" ,gure);
					DrawString(550, 40,"�~�̔�" ,kuro);
				}
				

				if( ProcessMessage() != 0 ){ // ���b�Z�[�W����
				break;//�E�B���h�E�́~�{�^���������ꂽ�烋�[�v�𔲂���
				}
				ScreenFlip(); //����ʂ�\��ʂɔ��f
		}
		}
		DxLib_End(); // DX���C�u�����I������
        return 0;
}