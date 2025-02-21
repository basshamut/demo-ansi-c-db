# Conexión Ansi C con PostgreSQL (Windows)

### Datos locales de conexión

- **Host:** `localhost:5432`
- **Username:** `postgres`
- **Password:** `1234`

### Construcción y Ejecución

- **Docker:**  docker run --name postgres -e POSTGRES_PASSWORD=1234 -d -p 5432:5432 postgres
- **Postgres:** ya el proyecto contiene las libs para la conexion con los drivers pero se tienen que configurar estas en las variables de entorno agregando la ruta base donde estan los DLL
- **Anci C:** para compilar usamos -> gcc main_postgres.c -o main_postgres.exe -I. -L. -lpq 

Luego de la compilación se generará un .exe que ya podremos ejecutar