# Localiza

Localiza é um script desenvolvido em C para a aula de Introdução a Programação, com a intenção de recriar funcionalidades do comando grep do Linux.

## Por de tras dos panos
O script recebe argumentos e começa o parsing dos mesmos.

Faz um loop pelos argumentos em busca de verificar a presença das flags.

Ao identificar as flags, consegue identificar to termo de busca e alvos sem muitas dificuldades.

Verifica a presença de um caractere coringa no termo de busca, se houver, dividi-se o termo no lugar de cada caractere.

Faz a identificação dos alvos e começa a procura pelo termo nos mesmos.

Para maiores detalhes sobre o funcionamento de cada função, olhar a documentação da função. Está localizada sobre a mesma nos arquivos.

## Modo de Uso

```Bash
./localiza [OPTIONS]... PATTERN [FILE|DIRECTORY]...
```