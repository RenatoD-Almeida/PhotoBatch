# Project: _PhotoBatch_

## Descritivo:

PhotoBach se trata de uma aplicação para manusear arquivos em lotes via linha de comando, visto que a inoportunidade de realizar a mesma tarefas para inumeros arquivos pode trazer ineficiência ao trabalho, A utilização dessa aplicação pode trazer diversos benefícios.

## Tag Help

O projeto foi integrado com modulos descritivos, como a flag help, que utilizada solo, trará a descrição geral do programa, e utilizando-a em conjunto com alguma flag, trará informações a respeito da flag desejada; E com uma macro "pDev" que, ao utilizar, não realiza nenhuma tarefa mas trás todo o relatório de flags e options ativas e os arquivos que serão trabalhados. 



### Flag Help sem nenhum modulo ativo
```
./app/photobatch --help
```

### Flag Help em conjunto, modulo ativo
```
./app/photobatch --scale --help
```

### Não realiza tarefas, apenas relatórios.

```
./app/PhotobatchpDev --rename --folder="/home/<username>/<workFolders> --Filter=".png" ...
```
### realiza tarefas, sem relatórios
```
./app/Photobatch --rename --folder="/home/<username>/<workFolders> --Filter=".png" ...
```
#

## Flags

Há 4 (quatro) flags cadastradas no PhotoBatch e são elas:

| Flags  | Descrição                            | Opções necessárias |
|--------|--------------------------------------|--------------------| 
|rename  |Renomeia Arquivos                     |Prefix e StartNumber| 
|Resize  |Redimensiona por medidas              |Width e Heigth      | 
|Convert |Converte extensão de imagem PGN e JPG |From e To           |
|Scale   |Redimensiona por escala               |Amount              |


### **Notas** : Todas as Flags utilizam as opções Folder e Filter
> Folder: Verifica se a pasta existe para que o programa possa realizar seu fluxo.

> Filter: Itera sobre os arquivos internos do Folder passado. Verificando se se trata de arquivos regulares, e o listando para arquivos desejados de trabalhar
#
### _**Rename**_

> Flag Rename tem como objetivo renomar os arquivos que foram parametrizados pela Option **Filter** para:
>
> Prefix + startNumber

Exemplo: Leve em consideração a existencia de uma pasta .../Images com 4 (quatro) imagens .png's; E os seguintes parâmetros:

> * Folder=/home/UserName/Documents/Images/
> * Filter=".png"
> * Preix="Imagem_"
> * StartNumber=1

Dessa Maneira:

```
./app/PhotoBatch --rename --Folder="/home/UserName/Documents/Images/" --Filter=".png" --Preix="Imagem_" --tartNumber=1
```
Os Arquivos seriam renomeados para:

1. "Imagem_1"
1. "Imagem_2"
1. "Imagem_3"
1. "Imagem_4"
#

### _**Convert**_


> Flag Convert tem como objetivo Converter os arquivos que foram parametrizados pela Option **Filter** e **From** para a Option **To**

> * Png -> Jpg/Jpeg
> * Jpg/Jpeg -> Png

Exemplo: Leve em consideração a existencia de uma pasta .../Images com 1 (uma) imagem com o nome FotoEmFamilia.png; E os seguintes parâmetros:

> * Folder=/home/UserName/Documents/Images/
> * Filter="Foto"
> * From="png" 
> * To="jpg"

Dessa Maneira:

```
./app/PhotoBatch --Convert --Folder="/home/UserName/Documents/Images/" --Filter="Foto" --From="png" --To="jpg"
```

Essa chamada irá gerar um arquivo de mesmo nome porém de outra extensão:
* FotoEmFamilia.png  -> FotoEmFamilia.jpg

#
### _**Resize**_

> Flag Resize tem como objetivo Redimensionar os arquivos que foram parametrizados pela Option **Filter** utilizando o **Width** e o **Height** como novas medidas

Exemplo: Leve em consideração a existencia de uma pasta .../Images com 1 (uma) imagem com o nome FotoEmFamilia.png com as seguintes dimensões: 600x320; E os seguintes parâmetros:

> * Folder=/home/UserName/Documents/Images/
> * Filter="Foto"
> * Width=1200
> * Height=640

Dessa Maneira:

```
./app/PhotoBatch --Convert --Folder="/home/UserName/Documents/Images/" --Filter="Foto" --Width=1200 --Height=640
```

Essa chamada irá redimensionar o arquivo de mesmo nome porém utilizando do _Width_ e _Height_ como suas novas dimensões:
* FotoEmFamilia.png 600x320  -> FotoEmFamilia.png 1200x640

#
### _**Scale**_

> Flag Scale tem como objetivo redimensionar por escala os arquivos que foram parametrizados pela Option **Filter**, usando a flag **amount** para calcular as novas dimensões da imagem

Exemplo: Leve em consideração a existencia de uma pasta .../Images com 1 (uma) imagem com o nome FotoEmFamilia.png; E os seguintes parâmetros:

> * Folder=/home/UserName/Documents/Images/
> * Filter="Foto"
> * Amount=0.5

Dessa Maneira:

```
./app/PhotoBatch --Convert --Folder="/home/UserName/Documents/Images/" --Filter="Foto" --amount=0.5
```

Essa chamada irá redimensionar o arquivo de mesmo nome porém, utilizando o _Amount_ para calcular sua nova dimensão:
* FotoEmFamilia.png (600x320)  -> FotoEmFamilia.png(300x160)

#