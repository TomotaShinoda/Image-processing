#include <stdio.h>
#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")

// 画像処理を学ぶため、画像処理のプログラムをライブラリ用いずに実装

struct RGB //各ピクセルのRGB値を格納する構造体
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
};

int main()
{
	// 画像情報を読み込むプログラムの実装
	
	//GdiPlusの有効化
	Gdiplus::GdiplusStartupInput Input;
	ULONG_PTR Token;
	Gdiplus::GdiplusStartup(&Token, &Input, NULL);

	int width = 0, height = 0;

	Gdiplus::Bitmap image(L"image_1.jpg"); //画像の読み込み

	//画像の幅，高さの取得
	width = image.GetWidth();
	height = image.GetHeight();

	Gdiplus::Color pixelColor; //ピクセルの色情報を取得するためのColorクラスのインスタンスを作成

	// RGB構造体の2次元配列のため，取得した高さ，幅をもとにメモリ確保
	RGB** pixel = new RGB * [width];
	for (int i = 0; i < width; i++) {
		pixel[i] = new RGB[height];
	}

	//RGB値読み取り
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			image.GetPixel(i, j, &pixelColor);
			pixel[i][j].R = pixelColor.GetR();
			pixel[i][j].G = pixelColor.GetG();
			pixel[i][j].B = pixelColor.GetB();
		}
	}

	// 以下ではいくつかの画像処理のプログラムを実装した（この状態では3.の二値化画像に変換を指定している）

	/*
	// 1. 各ピクセルの RGB 値を読み取り、元の値の半分に置き換え
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int red = pixel[i][j].R / 2;
			int green = pixel[i][j].G / 2;
			int blue = pixel[i][j].B / 2;
			Gdiplus::Color newpixel(red, green, blue);
			image.SetPixel(i, j, newpixel);
		}
	}
	*/
    /*
	// RGB値を１チャンネルに変換
	// GreyScale = 0.3R + 0.59G + 0.11B

	//グレースケールの輝度を格納する2次元配列の領域確保
	unsigned char** Grey = new unsigned char* [width];
	for (int i = 0; i < width; i++) {
		Grey[i] = new unsigned char[height];
	}

	//グレースケール輝度に変換
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			RGB tmp = pixel[i][j];
			Grey[i][j] = 0.30 * tmp.R + 0.59 * tmp.G + 0.11 * tmp.B;
		}
	}
	*/
	/*
	// 2. カラー画像をグレースケール画像に変換
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int gray = 0.29891 * pixel[i][j].R + 0.58661 * pixel[i][j].G + 0.11448 * pixel[i][j].B;
			Gdiplus::Color newpixel(gray, gray, gray);
			image.SetPixel(i, j, newpixel);
		}
	}
	*/
	///*
	// 3. 二値化画像に変換
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int gray = 0.29891 * pixel[i][j].R + 0.58661 * pixel[i][j].G + 0.11448 * pixel[i][j].B;
			if (gray > 100) { //しきい値を100より大きければ、輝度値255
				gray = 255;
			}
			else {            //しきい値を100より小さければ、輝度値0
				gray = 0;
			}
			Gdiplus::Color newpixel(gray, gray, gray);
			image.SetPixel(i, j, newpixel);
		}
	}
	//*/

	//---------------------------------------------------------------------------------------

	//画像ファイルをjpg形式で保存

	CLSID jpgClsid;
	CLSIDFromString(L"{557cf401-1a04-11d3-9a73-0000f81ef32e}", &jpgClsid);
	image.Save(L"out.jpg", &jpgClsid, NULL);

}

	
