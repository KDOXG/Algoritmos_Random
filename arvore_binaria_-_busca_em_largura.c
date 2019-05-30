int FilaTemElementos(arvore **fila, int tam)
{
    int i, flag=1;
    for (i=0; i<tam; i++)
    {
        if (fila[i] == NULL)
        {
            flag = 0;
            break;
        }
    }
    return flag;
}

arvore* GetNodo(arvore *nodo)
{
    if (nodo == NULL)
        return NULL;
    else
        return nodo;
}

void arvoreSimetrica(arvore *raiz, int quantidadeElementos)
{
    int *vetor, altura=2, filaTamanho=2, aux, i=0, j=0, k=1;
    arvore **filaNodos, **filaNodos_aux;
    filaNodos = malloc((altura)*sizeof(arvore*));
    filaNodos[0] = raiz->pEsq;
    filaNodos[1] = raiz->pDir;
    vetor = malloc(quantidadeElementos*sizeof(int));
    vetor[0] = raiz->dado; //Se o dado for um inteiro, senao so alterar o tipo do vetor
    for (i=0; i<filaTamanho; i++)
    {
        if (filaNodos[i] != NULL)
        {
            vetor[k] = filaNodos_aux[i]->dado;
            k++;
        }
    }

    for (filaTamanho=4; FilaVazia(filaNodos,filaTamanho); filaTamanho *= 2)
    {
        filaNodos_aux = malloc(filaTamanho*sizeof(arvore*));
        aux = altura;
        while (aux > 0)
        {
            filaNodos_aux[i] = GetNodo(filaNodos[j]->pEsq);
            i++;
            filaNodos_aux[i] = GetNodo(filaNodos[j]->pDir);
            i++;
            j++;
            aux--;
        }
        for (i=0; i<filaTamanho; i++)
        {
            if (filaNodos_aux[i] != NULL)
            {
                vetor[k] = filaNodos_aux[i]->dado;
                k++;
            }
        }
        free(filaNodos);
        filaNodos = filaNodos_aux;
        altura *= 2;
        i=0;
        j=0;
    }

    return;
}
