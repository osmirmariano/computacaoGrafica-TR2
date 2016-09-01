//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Paint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
	opcao = 0;
	Form3->Color = clWhite;

}

void __fastcall TForm3::PaintBox1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	x1 = X;
	y1 = Y;
	Form3->Color=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::PaintBox1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	switch(opcao){
		case 1:
			//Chamar o M�todo para reta
		   linha(x1,y1,X,Y);
			break;
		case 2:
			//Chamar o M�todo para retangulo
			retangulo(x1,y1,X,Y);
			break;
		case 3:
			//Chamar o M�todo para Circulo
			circunferencia(x1, y1, X, Y);
			break;
		case 4:
			//Chamar o M�todo para Polilinha Aberta
			polilinhaAberta(x1, y1, X, Y);
			break;
		case 5:
			//Chamar o M�todo para Polilinha Fechada
			break;
		case 6:
			//Chamar o M�todo para Balde de Tinta
			baldeTinta(x1, y1);
			break;
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//M�todo para Linha
void  TForm3::linha(float x1, float y1, float X, float Y){
	float m, b;

	//Realizando o tratamento para caso a coordenada final seja menor que a inicial.
	if(X < x1)
	{
		float recebe;//Variavel auxiliar para a troca
		recebe  = X;
		X  = x1;
		x1 = recebe;

		recebe = Y;
		Y = y1;
		y1 = recebe;
	}
	if(X == x1)//Condi��o para os casos em que n�o apresenta coeficiente angular
	{
		for(float i = y1; i <= Y; i++)
		{
			PaintBox1->Canvas->Pixels[X][i] = RGB(0,0,255);//clBlue;
		}
	}
	else
	{
		//C�lculo dos coeficientes angular e linear
		m = ((Y - y1)/(X - x1));
		b = (Y - (m * X));

		//Gerando e pintando a  reta.
		if( m >= (-1.0) && m <= 1)
		{
			for(float i = x1; i <= X; i++)
			{
				Y =( m * i) + b;
				PaintBox1->Canvas->Pixels [i][Y] = RGB(0,0,255);//clBlue;
			}
		}
		if(m > 1 || m < (-1.0))
		{
			if(Y < y1)
			{
				float B;
				B = Y;
				Y = y1;
				y1 = B;
			}
			for(float i = y1; i <= Y; i++)
			{
				X =(i - b) / m;
				PaintBox1->Canvas->Pixels[X][i] = RGB(0,0,255);//clBlue;
			}
		}
	}
}
//---------------------------------------------------------------------------
//------M�todo para gerar os ret�ngulos
void TForm3::retangulo(float x1, float y1, float X, float Y){
	float i;
	//Mesma quest�o da linha, verifica se a coordenada final � menor que a inicial em rela��o ao eixo X
	if(X < x1)
	{
		i  = X;
		X  = x1;
		x1 = i;
	}
	//Verifica��o em rela��o ao eixo Y
	if(Y < y1)
	{
		i  = Y;
		Y  = y1;
		y1 = i;
	}
	//For para percorrer e colorir as linhas nas horizontais
	for(i = x1; i <= X; i++)
	{
	   PaintBox1->Canvas->Pixels [i][y1] = clBlack;
	   PaintBox1->Canvas->Pixels [i][Y] = clBlack;
	}
	//For para percorrer e colorir as linhas nas verticais
	for(i = y1; i <= Y; i++)
	{
	   PaintBox1->Canvas->Pixels [x1][i] = clBlack;
	   PaintBox1->Canvas->Pixels [X][i] = clBlack;
	}
}
//---------------------------------------------------------------------------

//------M�todo para gerar os circulos
void   TForm3::circunferencia(float x1, float y1, float X, float Y){
	float distancia, raio, angulo, resultado;

	//Tr�s pontos em um plano cartesiano defini um circulo
	//Utilizando a formula da dist�ncia para calcular os tr�s lados
	distancia = (pow((X - x1),2)) + (pow((Y - y1),2));
	//Calculando a raiz do valor da dist�ncia do comprimento
	raio = sqrt(distancia);
	resultado = ((45/raio) * M_PI) / 180;

	for(angulo = 0; angulo < (2*M_PI); angulo += resultado)
	{
		X = x1 + raio * cos(angulo);
		Y = y1 + raio * sin(angulo);
		PaintBox1->Canvas->Pixels[X][Y]  = clRed;
	}
}
//---------------------------------------------------------------------------

void   TForm3::polilinhaAberta(float x1, float y1, float X, float Y){
	if(clickAtual == false)
	{
		x2 = x1;
		y2 = y1;
	}
	linha(x2,y2,X,Y);
	x2 = X;   //x2 recebe X, sen�o iria gerar linhas s� em torno do primeiro click
	y2 = Y;   //y2 recebe Y, sen�o iria gerar linhas s� em torno do primeiro click
	clickAtual = true;
}
//---------------------------------------------------------------------------
void   TForm3::baldeTinta(float x1, float y1){
	//Verifico se a cor do pixel � branco se for ai chamo recursivo at� n�o ser branco e assim colorindo
   if (PaintBox1->Canvas->Pixels[x1][y1] == clWhite) {
	   PaintBox1->Canvas->Pixels [x1][y1] = clGreen;
	   baldeTinta(x1+1, y1);
	   baldeTinta(x1, y1+1);
	   baldeTinta(x1-1, y1);
	   baldeTinta(x1, y1-1);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm3::SpeedButton1Click(TObject *Sender)
{
	opcao = 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::SpeedButton2Click(TObject *Sender)
{
	opcao = 2;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::SpeedButton3Click(TObject *Sender)
{
	opcao = 3;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::SpeedButton4Click(TObject *Sender)
{
	opcao = 4;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::SpeedButton6Click(TObject *Sender)
{
	opcao = 6;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::SpeedButton5Click(TObject *Sender)
{
	opcao = 5;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button1Click(TObject *Sender)
{
	Form3->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button2Click(TObject *Sender)
{
	Form3->CleanupInstance();
}
//---------------------------------------------------------------------------

