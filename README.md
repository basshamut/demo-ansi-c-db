# Conexión Ansi C con Mongo DB (Windows)

### Datos locales de conexión

- **Host:** `localhost:27017`
- **Username:** `mongo`
- **Password:** `1234`

### Construcción y Ejecución

- **Docker:**  docker run -d --name mongo_server -p 27017:27017 -e MONGO_INITDB_ROOT_USERNAME=mongo -e MONGO_INITDB_ROOT_PASSWORD=1234 mongo:latest
- **Mongo:** ya el proyecto contiene las libs para la conexion con los drivers pero se tienen que configurar tambien en las variables de entorno para esto se deben instalar los drivers en sus versiones para windows
- **Anci C:** para compilar usamos -> gcc main_mongo.c -o main_mongo.exe -I. -L. -lmongoc-1.0 -lbson-1.0

Luego de la compilación se generará un .exe que ya podremos ejecutar




