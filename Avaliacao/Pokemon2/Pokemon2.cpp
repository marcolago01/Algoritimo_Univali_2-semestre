#include "stdafx.h"
#include "tipos.h"
#include "golpes.h"
#include "golpesPokemons.h"
#include "pokemons.h"
#include "mensagens.h"
#include "mapa.h"
#include "capturaTeclado.h"
#include "jogadores.h"
#include "batalha.h"

int main()
{
	
	char mapa[TAMANHO_MAPA][TAMANHO_MAPA];
	preencherMatrizVazio(mapa);

	Pokemon todosPokemons[TOTALPOKEMONS];
	gerarPokemons(todosPokemons);

	bool acaoEsperarConfirmar = false;
	bool jogo = true;
	bool venceu = false;
	bool liderCriado = false;
	bool
		oponente1Derrotado = false,
		oponente2Derrotado = false,
		oponente3Derrotado = false,
		oponente4Derrotado = false;
	char teclaEscolhida;

	int liberarLider = 0;

	const int TOTALOPONENTES = 4;

	Jogadores jogador = criarJogador(mapa, escolherPokemons(todosPokemons), escolherPokemons(todosPokemons));

	Jogadores oponente1 = criarOponente(mapa, escolherPokemons(todosPokemons), escolherPokemons(todosPokemons));
	Jogadores oponente2 = criarOponente(mapa, escolherPokemons(todosPokemons), escolherPokemons(todosPokemons));
	Jogadores oponente3 = criarOponente(mapa, escolherPokemons(todosPokemons), escolherPokemons(todosPokemons));
	Jogadores oponente4 = criarOponente(mapa, escolherPokemons(todosPokemons), escolherPokemons(todosPokemons));
	Jogadores liderGinasio;
	CentroPokemon centroPokemon = criarCentroPokemon(mapa);

	cercas(mapa);
	do {
		renderizarMapa(mapa);
		exibirMenuMovimentacao();
		do {
			teclaEscolhida = capturarTecla<char>();
			if (!teclasValidas(teclaEscolhida)) {
				system("cls");
				renderizarMapa(mapa);
				exibirMensagemTeclaErrada();
				exibirMenuMovimentacao();
			}
		} while (!teclasValidas(teclaEscolhida));

		acaoTeclas(teclaEscolhida, mapa, jogador, acaoEsperarConfirmar);
		system("cls");

		if (!oponente1Derrotado) {
			movimentoOponente(mapa, oponente1, jogador);
		}
		if (!oponente2Derrotado) {
			movimentoOponente(mapa, oponente2, jogador);
		}
		if (!oponente3Derrotado) {
			movimentoOponente(mapa, oponente3, jogador);
		}
		if (!oponente4Derrotado) {
			movimentoOponente(mapa, oponente4, jogador);
		}

		if (OponenteAdjacentJogador(mapa, oponente1)) {
			jogo = iniciarBatalha(jogador.pokemons, oponente1.pokemons);
			if (jogo) {
				mapa[oponente1.linha][oponente1.coluna] = VAZIO;
				oponente1.linha = -1;
				oponente1.coluna = -1;
				liberarLider++;
				oponente1Derrotado = true;
			}
		}
		else if (OponenteAdjacentJogador(mapa, oponente2)) {
			jogo = iniciarBatalha(jogador.pokemons, oponente2.pokemons);
			if (jogo) {
				mapa[oponente2.linha][oponente2.coluna] = VAZIO;
				oponente2.linha = -1;
				oponente2.coluna = -1;
				liberarLider++;
				oponente2Derrotado = true;
			}
		}
		else if (OponenteAdjacentJogador(mapa, oponente3)) {
			jogo = iniciarBatalha(jogador.pokemons, oponente3.pokemons);
			if (jogo) {
				mapa[oponente3.linha][oponente3.coluna] = VAZIO;
				oponente3.linha = -1;
				oponente3.coluna = -1;
				liberarLider++;
				oponente3Derrotado = true;
			}
		}
		else if (OponenteAdjacentJogador(mapa, oponente4)) {
			jogo = iniciarBatalha(jogador.pokemons, oponente4.pokemons);
			if (jogo) {
				mapa[oponente4.linha][oponente4.coluna] = VAZIO;
				oponente4.linha = -1;
				oponente4.coluna = -1;
				liberarLider++;
				oponente4Derrotado = true;
			}
		}
		if (liberarLider == TOTALOPONENTES) {
			if (!liderCriado) {
				liderGinasio = criarLiderGinasio(mapa, escolherPokemons(todosPokemons), escolherPokemons(todosPokemons));
				liderCriado = true;
			}
			if (OponenteAdjacentJogador(mapa, liderGinasio)) {
				jogo = iniciarBatalha(jogador.pokemons, liderGinasio.pokemons);
				if (jogo) {
					venceu = true;
					jogo = false;
				}
			}
		}
	} while (jogo);
	if (venceu) {
		exibirVitoria();
	}
	else {
		gameOver();
	}
	system("pause");
	
}
