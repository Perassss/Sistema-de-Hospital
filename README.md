Este projeto é um sistema de gestão hospitalar desenvolvido em C, concebido para facilitar o controlo e o armazenamento de informações relacionadas com pacientes, procedimentos médicos e recursos hospitalares. Abaixo, segue uma descrição detalhada:

Funcionalidades Principais:
Gestão de Pacientes:

Permite registar pacientes com informações detalhadas, como:
Nome;
Idade;
Sexo (M/F);
Número SNS (Sistema Nacional de Saúde);
Nível de urgência (0-10).
Inclui funcionalidades para listar todos os pacientes, procurar um paciente específico pelo número SNS, editar os seus dados ou eliminá-lo do sistema.
Gestão de Procedimentos Médicos:

Possibilita o registo de procedimentos futuros associados a pacientes, incluindo:
Número SNS do paciente;
Quantidade de procedimentos planeados;
Descrição detalhada dos procedimentos.
Oferece a opção de listar todos os procedimentos e de guardar ou carregar os dados de um ficheiro.
Gestão de Recursos Hospitalares:

Permite registar recursos hospitalares, como medicamentos ou equipamentos, especificando:
Tipo de recurso;
Nome ou descrição do serviço;
Quantidade disponível.
Inclui funcionalidades para listar todos os recursos e gerir a persistência dos mesmos em ficheiros.
Consultas por Filtros:

Possibilita pesquisar pacientes com base em critérios específicos:
Idade;
Sexo (M/F);
Nível de urgência;
Quantidade de procedimentos associados.
Persistência de Dados:

Garante a integridade dos dados ao permitir que pacientes, procedimentos e recursos sejam guardados em ficheiros e carregados novamente ao iniciar o sistema.
Menu Interativo:

Apresenta um menu intuitivo com as seguintes opções:
Inserir novo paciente, procedimento ou recurso;
Listar registos em memória;
Consultar registos específicos;
Editar ou eliminar um paciente;
Guardar os dados em ficheiros para uso futuro.
Estrutura do Projeto:
hospital.h: Contém as definições das estruturas de dados (Paciente, Procedimento e Recurso) e as declarações das funções utilizadas no projeto.
hospital.c: Implementa as funcionalidades principais do sistema, como inserção, listagem, edição, consulta e eliminação de registos.
main.c: É responsável pela interface com o utilizador, controlando o menu interativo e integrando as operações disponíveis no sistema.
Objectivo:
Este sistema foi concebido para ser uma ferramenta prática e simples de utilizar, permitindo o controlo básico de informações hospitalares. É ideal para registos simples e armazenamento de dados de forma persistente, garantindo um funcionamento eficiente em contextos hospitalares de pequena escala.
