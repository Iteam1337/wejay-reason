FROM node:10.4-alpine
RUN apk update && apk add python make g++

WORKDIR /app/

# Global installation
RUN npm install -g --unsafe-perm reason-cli@3.2.0-linux serve

# Copy and install
COPY package*json ./
COPY ./src ./src
COPY bsconfig.json ./bsconfig.json
COPY graphql_schema.json ./graphql_schema.json
COPY webpack.config.js ./webpack.config.js
RUN npm install

EXPOSE 3000

CMD ["sh", "-c", "npm run build && npm run webpack:production && serve -s build"]
