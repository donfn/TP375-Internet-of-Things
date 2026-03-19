FROM openjdk:11

COPY ./java /usr/src/myapp

WORKDIR /usr/src/myapp

RUN javac Hello.java

CMD ["java","Hello"]
