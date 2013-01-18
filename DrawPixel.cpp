
#include "DxLib.h"


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){

    SetMainWindowText( "○×ゲーム" ) ;

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
	//前処理終了
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
				SetDrawScreen( DX_SCREEN_BACK ); //描画先を裏画面に設定
				
				for(i = 0; i<3; i++){
					for(j=0; j<3; j++){ 
						flgu[i][j] = 0;
					}}
		 //フラグの初期化
				batu_h = LoadGraph( "画像/batu.png" );
				maru_h = LoadGraph( "画像/maru.png" );
				bg_h = LoadGraph( "画像/bg.png" );// 画像をロード
      
				kuro = GetColor(0, 0, 0) ;
				gure = GetColor(160, 160, 160) ;// 色の値を取得

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
				}//クリック
			
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
					DrawString( 20 ,40 , "○の番" ,kuro );
					DrawString( 550 ,40 , "×の番" ,gure);
				}else{
					DrawString(20, 40, "○の番" ,gure);
					DrawString(550, 40,"×の番" ,kuro);
				}
				

				if( ProcessMessage() != 0 ){ // メッセージ処理
				break;//ウィンドウの×ボタンが押されたらループを抜ける
				}
				ScreenFlip(); //裏画面を表画面に反映
		}
		}
		DxLib_End(); // DXライブラリ終了処理
        return 0;
}