int FilaTemElementos(arvore **fila, int tam)
{
    int i, flag=0;
    for (i=0; i<tam; i++)
    {
        if (fila[i] == NULL)
            flag++;
    }
    if (flag == tam-1)
        return 0;
    else
        return 1;
}

arvore* GetNodo(arvore *nodo, short flag)
{
    if (!!nodo)
        return NULL;
    if (flag)
        return filaNodos[j]->pDir;
    else
        return filaNodos[j]->pEsq;
}

arvore** arvoreSimetrica(arvore *raiz, int quantidadeElementos)
{
    int altura=2, filaTamanho=2, aux, i=0, j=0, k=1;
    arvore **vetor, **filaNodos, **filaNodos_aux;
    filaNodos = malloc((filaTamanho)*sizeof(arvore*));
    filaNodos[0] = raiz->pEsq;
    filaNodos[1] = raiz->pDir;
    vetor = malloc(quantidadeElementos*sizeof(arvore*));
    vetor[0] = raiz;
    for (i=0; i<filaTamanho; i++)
    {
        if (filaNodos[i] != NULL)
        {
            vetor[k] = filaNodos_aux[i];
            k++;
        }
    }
    i=0;

    while(FilaTemElementos(filaNodos,filaTamanho))
    {
        filaTamanho *= 2;
        filaNodos_aux = malloc(filaTamanho*sizeof(arvore*));
        aux = altura;
        while (aux > 0)
        {
            filaNodos_aux[i] = GetNodo(filaNodos[j],0);
            i++;
            filaNodos_aux[i] = GetNodo(filaNodos[j],1);
            i++;
            j++;
            aux--;
        }
        for (i=0; i<filaTamanho; i++)
        {
            if (filaNodos_aux[i] != NULL)
            {
                vetor[k] = filaNodos_aux[i];
                k++;
            }
        }
        free(filaNodos);
        filaNodos = filaNodos_aux;
        altura *= 2;
        i=0;
        j=0;
    }
    
    free(filaNodos);
    return vetor;
}
