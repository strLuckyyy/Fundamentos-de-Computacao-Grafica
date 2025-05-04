# Parte 1 - Teoria

1. O que é a GLSL? Quais os dois tipos de shaders são obrigatórios no pipeline programável da versão atual que trabalhamos em aula e o que eles processam?

r: 
GLSL é a linguagem de programação usada para criar shaders no OpenGL. Ela permite controlar como os objetos são renderizados, desde a posição até a cor final.

Na versão 3.3/3.4, os dois shader obrigatórios são:

* **Vertex Shader** – Processa cada vértice do objeto, definindo sua posição na tela e passando dados (como cores ou texturas) para o próximo estágio.
* **Fragment Shader** – Decide a cor de cada pixel (fragmento), aplicando texturas, iluminação e efeitos visuais.

-----------------------------------------------------------------------------------------
2. O que são primitivas gráficas? Como fazemos o armazenamento dos vértices na OpenGL?

r:
Primitivas são os blocos básicos que o OpenGL usa para desenhar. Pontos, linhas e triângulos.

Para guardar os vértices, usamos o VBO e o VAO. 

------------------------------------------------------------------------------------------
3. Explique o que é VBO e VAO, e como se relacionam (se achar mais fácil, pode fazer um gráfico
representando a relação entre eles).

r:
O **VBO** armazena na GPU os dados brutos dos vértices (posições, cores, normais). Ele contém apenas os valores, sem saber como serão usados.

O **VAO** organiza como esses dados são lidos. Ele referencia os VBOs e guarda as configurações de interpretação (formato, tipo e tamanho dos atributos). Um mesmo VBO pode ser usado por vários VAOs.

Na prática: você cria VBOs com os dados, depois configura VAOs para dizer como usá-los. Durante o rendering, basta vincular o VAO - ele já sabe qual VBO usar e como processá-lo. Isso torna o desenho mais eficiente e organizado.

-------------------------------------------------------------------------------------------
4. Como são feitas as chamadas de desenho na OpenGL? Para que servem as primitivas de desenho?

r:
Na OpenGL, usamos funções como **glDrawArrays** e **glDrawElements** para desenhar. 
Elas transformam os dados dos vértices em objetos visíveis na tela.
As primitivas **(GL_POINTS, GL_LINES, GL_TRIANGLES)** definem como esses vértices se conectam; 
se viram pontos soltos, linhas ou triângulos.

Sem elas, a GPU não saberia como juntar os vértices. 
Primeiro configuramos os buffers (VBO) com os dados, depois um VAO explica como ler esses dados. 
Na hora de renderizar, basta chamar **glDrawArrays(GL_TRIANGLES, 0, 3)** para desenhar um triângulo, por exemplo. 
É assim que dados brutos viram imagens na tela.

-------------------------------------------------------------------------------------------
5. Analise o código fonte do projeto Hello Triangle. Localize e relacione os conceitos de shaders, VBOs e VAO apresentados até então. Não precisa entregar nada neste exercício.

r:
No código Hello Triangle, os conceitos aparecem assim:

Os shaders estão definidos nas strings vertexShaderSource e fragmentShaderSource. O vertex shader processa as posições dos vértices, enquanto o fragment shader define a cor do triângulo. Eles são compilados e linkados na função setupShader().

O VBO é criado em setupGeometry() com glGenBuffers() e glBufferData(), armazenando as coordenadas dos vértices do triângulo. O VAO também é criado ali com glGenVertexArrays() e configurado com glVertexAttribPointer() para dizer como ler os dados do VBO.

Na renderização principal, o VAO é ativado com glBindVertexArray() antes do glDrawArrays(), que usa os shaders e os buffers configurados para desenhar o triângulo. Tudo funciona junto: os shaders processam os dados, o VBO armazena eles e o VAO organiza como devem ser lidos.