// Hotel.cpp - Programa de Hotel para prova de Linguagem de Programa��o - 05/04/2017
// FATEC - Mogi das Cruzes
#include "Hotel.h"
//
// Fun��o principal
//
void main(void)
{
	int  i,									// indice gen�rico
		iIndQuarto,							// para calcular o �ndice do quarto em fun��o do
											// andar e o quarto dentro do andar
		nQtdeAndares,						// para receber a quantidade de andares do hotel
		nQtdeQuartosPorAndar,				// para receber a quantidade de quartos por andar
		nAndarHotel,						// para receber o n�mero do andar
		nQuartoHotel;						// para receber o n�mero do quarto dentro do andar
	char cOpcaoOper,						// local para receber a op��o escolhida do menu
		cNomeHospede[41],					// local para receber o nome do h�spede do hotel
		cWork[200],							// para formata��o de sprintf
		cNomeAluno[] = "Otavio Augusto Marinho Porto";
	double dValor;							// local para receber o valor dos servi�os do hotel
	//
	// vetores do sistema de hotel
	//
	// o vetor abaixo indica quando o quarto dentro de um andar  est� livre ou ocupado
	//		true - indica que o quarto est� ocupado
	bool vetLivreOcupado[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	// o vetor bi-dimensional abaixo indica o nome do hospede que est� ocupando o quarto
	char vetNomeHospede[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS][EXTEN_NOME + 1];
	// o vetor abaixo indica o valor da di�ria do quarto
	double vetVlrDiaria[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	// o vetor abaixo indica o valor total de di�rias do quarto
	double vetTotalDiarias[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	SYSTEMTIME stTime;						// para buscar data e hora

	setlocale(LC_ALL, "portuguese_brazil");
	// comandos para estabelecer o numero de casas decimais
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);						// duas casas decimais
	// <<<<<<0>>>>>>> - Antes de entregar o Pen drive - renomear o diret�rio principal do projeto que
	// est� LP_ProvaN1_05_04_2017_Noite para LP_ProvaN1_SeuNomeComLetrasMai�sculasMin�sculas

	// <<<< 01 >>>>
	// Preencher seu nome em cNomeAluno
	// Pedir a quantidade de andares e quartos por andar do hotel ou zeros para cancelar a
	//	execu��o do programa
	// A quantidade de andares n�o pode ser menor que QTDE_MINIMA_ANDARES e n�o pode ser maior
	//	que a QUANTIDADE_MAXIMA_ANDARES. Se for informado zeros cancelar a execu��o do programa
	do
	{
		cout << "Digite a quantidade de andares entre " << QTDE_MINIMA_ANDARES << " e " << QUANTIDADE_MAXIMA_ANDARES << " ou ZERO para cancelar: ";
		cin >> nQtdeAndares;
		if (nQtdeAndares == 0)
			return;
	}while(nQtdeAndares < QTDE_MINIMA_ANDARES || nQtdeAndares > QUANTIDADE_MAXIMA_ANDARES);
	// A quantidade de quartos por andar n�o pode ser menor que QTDE_MINIMA_QUARTOS_ANDAR
	//  ou maior que QUANTIDADE_MAXIMA_QUARTOS. Se for informado zeros cancelar a execu��o do
	//	programa.
	do
	{
		cout << "Digite a quantidade de quartos entre " << QTDE_MINIMA_QUARTOS_ANDAR << " e " << QUANTIDADE_MAXIMA_QUARTOS << " ou ZERO para cancelar: ";
		cin >> nQtdeQuartosPorAndar;
		if (nQtdeQuartosPorAndar == 0)
			return;
	}while(nQtdeQuartosPorAndar < QTDE_MINIMA_QUARTOS_ANDAR || nQtdeQuartosPorAndar > QUANTIDADE_MAXIMA_QUARTOS);
	//
	// Inicializar o vetor vetLivreOcupado fazendo com que todos os quartos estejam livres e 
	//		associar a cada quarto o valor correspondente da di�ria de acordo com o andar do
	//		mesmo de acordo com que foi definido no Hotel.h
	//		Zerar o total de di�rias de cada quarto.
	for(i = 0; i < (nQtdeAndares * nQtdeQuartosPorAndar); i++)
	{
		vetLivreOcupado[i] = false;
		vetTotalDiarias[i] = 0;
		if(i <= 19)				// quartos at� o segundo andar?
			vetVlrDiaria[i] = DIARIA_QUARTO_SIMPLES;
		else if(i <= 39)		// quartos at� o quarto andar?
			vetVlrDiaria[i] = DIARIA_QUARTO_MEDIO;
		else if(i <= 79)		// quartos at� o oitavo andar?
			vetVlrDiaria[i] = DIARIA_QUARTO_SUPER;
		else					// quartos do andar 9 para cima
			vetVlrDiaria[i] = DIARIA_QUARTO_SUITE;
	}

	while(true)								// loop infinito
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);
		sprintf_s(cWork, sizeof(cWork), 
			"\n\tFATEC-MC - Sistema de Hotel %02d/%02d/%04d �s %02d:%02d:%02d\n\t\tOperador: %s Turma: Noite",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno);
		cout << cWork << endl;
		// Mostrar o menu de op��es para o operador
		cout << FAZER_CHECK_IN << " - Check-in de um hospede" << endl;
		cout << FAZER_CHECK_OUT << " - Check-out de um hospede" << endl;
		cout << LANCAR_DIARIA << " - Lancar diarias em todos os quartos ocupados" << endl;
		cout << LISTAR_UM_QUARTO << " - Listar um quarto" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin	 >> cOpcaoOper;					// op��o escolhida pelo operador
		cOpcaoOper = toupper(cOpcaoOper);	// converte para upper case a op��o escolhida
		switch(cOpcaoOper)					// avaliar a op��o que foi escolhida pelo operador
		{
			case FAZER_CHECK_IN:
				// <<<< 02 >>>>
				// 1 - Chamar a fun��o PedirAndarQuarto passando os endere�o de nAndarHotel para receber
				//		o n�mero do andar e o endere�o de nQuartoHotel para receber o n�mero do quarto no
				//			andar, quantidade de andares e quartos por andar que foram configurados e
				//			indicar que a transa��o � "Check-in de h�spede"
				//		Se retornar false cancelar a transa��o e voltar ao menu
				// somente para testes
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, 
					nQtdeAndares, nQtdeQuartosPorAndar, "Check-in de um h�spede"))
					break;									// sai do switch e volta ao menu
				// 2 - Se retornou true indicando que foram informados andar e quarto no andar v�lido
				//		calcular o iIndQuarto em fun��o do andar e quarto no andar informados.
				else
				{
					iIndQuarto = ((nAndarHotel -1)*nQtdeQuartosPorAndar)+(nQuartoHotel-1);
				// 3 - Verificar se o quarto j� est� ocupado e se estiver exibir ao operador que o
				//		quarto est� ocupado e o nome do h�spede que est� ocupando o quarto, dar uma
				//		pausa para o operador poder ler e voltar ao menu.
					if (vetLivreOcupado[iIndQuarto])			// quarto est� ocupado?
					{
						cout << "O quarto " << nQuartoHotel << "esta ocupado pelo hospede: " << vetNomeHospede[iIndQuarto] << endl;
						PAUSA;
						break;
					}
					else
					{
				// 4 - Pedir o nome do h�spede considerando que tem nome e sobrenome
						cin.ignore(1,EOF);
						cout << "Digite o nome do hospede: ";
						cin.getline(&vetNomeHospede[iIndQuarto][0],40);
				// 5 - Zerar o total de di�rias do quarto que est� sendo ocupado
						vetTotalDiarias[iIndQuarto] = 0;
				// 6 - Indicar que este quarto est� ocupado e voltar ao menu
						vetLivreOcupado[iIndQuarto] = true;
					}
				}
				break;						// para sair do switch e voltar ao menu
			case FAZER_CHECK_OUT:
				// <<<< 03 >>>>
				// 1 - Pedir o andar e o quarto da mesma forma que no item anterior indicando que a transa��o 
				//		� "Check-out"
				// 2 - Verificar se a transa��o foi cancelada e voltar ao menu
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, 
					nQtdeAndares, nQtdeQuartosPorAndar, "Check-out de um h�spede"))
					break;									// sai do switch e volta ao menu
				else
				{
					iIndQuarto = ((nAndarHotel -1)*nQtdeQuartosPorAndar)+(nQuartoHotel-1);
				// 3 - Verificar se o quarto est� ocupado e se estiver exibir o nome do h�spede e
				//		o total de di�rias do quarto
					if (vetLivreOcupado[iIndQuarto])		// quarto esta ocupado?
					{
						cout << "Hospede: " << vetNomeHospede[iIndQuarto] << "\t" << "Total de diarias: " << vetTotalDiarias[iIndQuarto] << endl;
				// 4 - Pedir a confirma��o do operador com um S ou N
				//		Se for indicado 'S' ou 's' desocupar o quarto e qualquer outro caractere 
				//		 voltar ao menu. Para desocupar o quarto basta indicar false no vetLivreOcupado
						cout << "Digite 'S' para confirmar o Check-out ou 'N' para cancelar a opera��o: ";
						cin	 >> cOpcaoOper;					// op��o escolhida pelo operador
						cOpcaoOper = toupper(cOpcaoOper);	// converte para upper case a op��o escolhida
						if (cOpcaoOper == 'S')
							vetLivreOcupado[iIndQuarto] = false;		//indica que o quarto est� desocupado
						else
						{
							PAUSA;
							break;
						}
					}
					else
					{
				// 5 - Se o quarto n�o estiver ocupado avisar ao operador e voltar ao menu
					cout << "O quarto " << nQuartoHotel << " do andar " << nAndarHotel << " esta livre."<< endl;
					PAUSA;
					break;
					}
				}
				break;						// para sair do switch e voltar ao menu
			case LANCAR_DIARIA:
				// <<<< 05 >>>> 
				// 1 - Pedir a data e hora do sistema e apresentar ao operador
				GetLocalTime(&stTime);
				sprintf_s(cWork, sizeof(cWork),
					"\nDeseja lan�ar di�ria em %02d/%02d/%04d?\nConfirma? (S ou N): ",
					stTime.wDay, stTime.wMonth, stTime.wYear);
				cout << cWork;								
				// 2 - Confirmar com o operador se ele realmente deseja lan�ar as di�rias no hor�rio
				//		apresentado
				cin	 >> cOpcaoOper;					// op��o escolhida pelo operador
				cOpcaoOper = toupper(cOpcaoOper);	// converte para upper case a op��o escolhida
				if (cOpcaoOper == 'S')
				{
				// 3 - Se o operador confirmar percorrer o vetor de quartos livres e ocupados e 
				//			somar uma di�ria a mais no total de di�rias dos quartos ocupados.
				for(i = 0; i < (nQtdeAndares * nQtdeQuartosPorAndar); i++)
					{
						if (vetLivreOcupado[i])		//quarto est� ocupado?
						{
						if(i <= 19)			// quartos at� o segundo andar?
							vetTotalDiarias[i] = vetTotalDiarias[i] + DIARIA_QUARTO_SIMPLES;
						else if(i <= 39)	// quartos at� o quarto andar?
							vetTotalDiarias[i] = vetTotalDiarias[i] + DIARIA_QUARTO_MEDIO;
						else if(i <= 79)	// quartos at� o oitavo andar?
							vetTotalDiarias[i] = vetTotalDiarias[i] + DIARIA_QUARTO_SUPER;
						else				// quartos do andar 9 para cima
							vetTotalDiarias[i] = vetTotalDiarias[i] + DIARIA_QUARTO_SUITE;
						}
					}	
				}
				else
				{
				// 4 - Caso o operador n�o confirme voltar ao menu.
					break;
				}
				//		Lan�ar di�ria significa pegar o valor da di�ria que foi associada ao quarto e
				//			somar no total das di�rias e do quarto.
				// Para buscar a data e hora do sistema utilizar o seguinte comando:
				//		GetLocalTime(&stTime);
				//		stTime.wDay, stTime.wHour e etc. tem o valores correspondentes a data e hora
				break;						// para sair do switch e voltar ao menu
			case LISTAR_UM_QUARTO:
				// <<<< 06 >>>> 
				// 1 - Pedir Andar e Quarto conforme itens anteriores
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, 
					nQtdeAndares, nQtdeQuartosPorAndar, "Check-in de um h�spede"))
					break;									// sai do switch e volta ao menu
				else
				{
					iIndQuarto = ((nAndarHotel -1)*nQtdeQuartosPorAndar)+(nQuartoHotel-1);
				// 2 - Verificar se o quarto est� ocupado e se n�o estiver, avisar ao operador e voltar ao menu
					if (vetLivreOcupado[iIndQuarto])
					{
				// 3 - Se estiver ocupado listar os dados do quarto indicando nome do h�spede e valor da
				//		di�ria do quarto e o total de di�rias utilizando o sprintf_s
				//		Formato: Andar Quarto H�spede            Vlr.Di�ria Tot.Di�rias
				//				  A      Q    XXXXXXXXXXXXXXXXX  DDDDD.DD   TTTTTT.TT
				//
						cout << "Andar Quarto Hospede            Vlr.Diaria Tot.Diarias" << endl;
						sprintf_s(cWork,sizeof(cWork),
							" %d      %d    %-16s   %5.2f     %6.2f",
							nAndarHotel,nQuartoHotel,vetNomeHospede[iIndQuarto],vetVlrDiaria[iIndQuarto],vetTotalDiarias[iIndQuarto]);
						cout << cWork << endl;
						PAUSA;
						break;
					}
					else
					{
						cout << "O quarto " << nQuartoHotel << " do andar " << nAndarHotel << " nao esta ocupado." << endl;
						PAUSA;
						break;
					}

				}
				break;						// para sair do switch e voltar ao menu
			case SAIR_DO_PROGRAMA:
				cout << "\nDeseja sair realmente? (S ou N): ";
				cin >> cOpcaoOper;
				if(cOpcaoOper == 'S' || cOpcaoOper == 's')		// sair realmente?
					return;
				break;						// para sair do switch e decidir se vai sair realmente
			default:
				// Avisar que foi escolhida uma op��o errada
				cout << "\nOpcao inv�lida!" << endl;
				PAUSA;
		} // switch
	} // while(true)
} // main
