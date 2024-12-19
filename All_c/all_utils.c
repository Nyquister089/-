
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <mysql/mysql.h>

#include "db.h"
#include "../model/trpdb.h"

void print_stmt_error (MYSQL_STMT *stmt, char *message)
{
	fprintf (stderr, "%s\n", message);
	if (stmt != NULL) {
		fprintf (stderr, "Error %u (%s): %s\n",
			 mysql_stmt_errno (stmt),
			 mysql_stmt_sqlstate(stmt),
			 mysql_stmt_error (stmt));
	}
}

void print_error(MYSQL *conn, char *message)
{
	fprintf (stderr, "%s\n", message);
	if (conn != NULL) {
#if MYSQL_VERSION_ID >= 40101
		fprintf (stderr, "Error %u (%s): %s\n",
			 mysql_errno (conn), mysql_sqlstate(conn), mysql_error (conn));
#else
		fprintf (stderr, "Error %u: %s\n",
		mysql_errno (conn), mysql_error (conn));
#endif
	}
}


bool setup_prepared_stmt(MYSQL_STMT **stmt, char *statement, MYSQL *conn)
{   
	bool update_length = true;

	*stmt = mysql_stmt_init(conn);
	if (*stmt == NULL)
	{
		print_error(conn, "Could not initialize statement handler");
		return false;
	}

	if (mysql_stmt_prepare (*stmt, statement, strlen(statement)) != 0) {
		print_stmt_error(*stmt, "Could not prepare statement");
		return false;
	}
	
	mysql_stmt_attr_set(*stmt, STMT_ATTR_UPDATE_MAX_LENGTH, &update_length);

	return true;
}

void finish_with_error(MYSQL *conn, char *message)
{
	print_error(conn, message);
	mysql_close(conn);
	exit(EXIT_FAILURE);
}

void finish_with_stmt_error(MYSQL *conn, MYSQL_STMT *stmt, char *message, bool close_stmt)
{
	print_stmt_error(stmt, message);
	if(close_stmt)
		mysql_stmt_close(stmt);
	mysql_close(conn);
	exit(EXIT_FAILURE);
}


void set_binding_param(MYSQL_BIND *param, enum enum_field_types type, void *buffer, unsigned long len)
{
	memset(param, 0, sizeof(*param));

	param->buffer_type = type;
	param->buffer = buffer;
	param->buffer_length = len;
}


void date_to_mysql_time(char *str, MYSQL_TIME *time)
{
	memset(time, 0, sizeof(*time));
	sscanf(str, "%4d-%2d-%2d", &time->year, &time->month, &time->day);
	time->time_type = MYSQL_TIMESTAMP_DATE;
}


void time_to_mysql_time(char *str, MYSQL_TIME *time)
{
	memset(time, 0, sizeof(*time));
	sscanf(str, "%02d:%02d", &time->hour, &time->minute);
	time->time_type = MYSQL_TIMESTAMP_TIME;
}

void init_mysql_timestamp(MYSQL_TIME *time)
{
	memset(time, 0, sizeof (*time));
	time->time_type = MYSQL_TIMESTAMP_DATETIME;
}

void init_mysql_date(MYSQL_TIME *time)
{
	memset(time, 0, sizeof (*time));
	time->time_type = MYSQL_TIMESTAMP_DATE;
}


void mysql_timestamp_to_string(MYSQL_TIME *time, char *str)
{
	snprintf(str, DATETIME_LEN, "%4d-%02d-%02d %02d:%02d", time->year, time->month, time->day, time->hour, time->minute);
}

void mysql_time_to_string(MYSQL_TIME *time, char *str)
{
	snprintf(str, TIME_LEN, "%02d:%02d", time->hour, time->minute);
}

void mysql_date_to_string(MYSQL_TIME *date, char *str)
{
	snprintf(str, DATE_LEN, "%4d-%02d-%02d", date->year, date->month, date->day);
}

int exe_proc(MYSQL_STMT *procedure,  char * buff){

if(mysql_stmt_execute(procedure) != 0) {
		printf("Procedura : %s \n", buff);
		print_stmt_error(procedure, "\nImpossibile eseguire execute ");
		return -1;
	}
	return 0; 
}

size_t bind_exe(MYSQL_STMT *procedure, MYSQL_BIND *param, char * buff)
{

if(mysql_stmt_bind_param(procedure, param) != 0) {
		printf("Procedura : %s \n", buff);
		print_stmt_error(procedure, "\nImpossibile eseguire bind param");
		return-1;
	}
	if(mysql_stmt_execute(procedure) != 0) {
		printf("Procedura : %s \n", buff);
		print_stmt_error(procedure, "\nImpossibile eseguire execute ");
		return -1;
	}

	return 0;
}

int take_result(MYSQL_STMT *procedure, MYSQL_BIND *param, char *buff)
{ 	
	int status; 
 
	if(mysql_stmt_bind_result(procedure, param)!=0) {
		printf("Procedura : %s ",buff);
		print_stmt_error(procedure, "\n\n Impossibile eseguire il bind result\n\n");
		return -1; 
	}
	
	
	if( mysql_stmt_store_result(procedure) != 0){
		printf("Procedura : %s", buff); 
		print_stmt_error(procedure, "\nImpossibile eseguire store result");
		return -1;
	}

	while (true) {
		status = mysql_stmt_fetch(procedure);
		if (status == MYSQL_NO_DATA)
			break; 
		if (status == 1 ){
			printf("Procedura : %s", buff);
			print_stmt_error(procedure, "\nImpossibile eseguire fetch ");
			return -1;
			}
	}
	return mysql_stmt_num_rows(procedure);
}

size_t take_rows(MYSQL_STMT *procedure, char *buff)
{
	if(mysql_stmt_execute(procedure) != 0) {
		printf("Procedura : %s", buff);
		print_stmt_error(procedure, " \nImpossibile eseguire execute "); 
		return -1; 
	}
		
	if( mysql_stmt_store_result(procedure) != 0){
		printf("Procedura : %s", buff);
		print_stmt_error(procedure, "\nImpossibile eseguire store result");
		return -1; 
	}
	return mysql_stmt_num_rows(procedure);
}
#pragma once

#include <stdbool.h>
#include <mysql/mysql.h>

extern void print_stmt_error (MYSQL_STMT *stmt, char *message);
extern void print_error(MYSQL *conn, char *message);
extern bool setup_prepared_stmt(MYSQL_STMT **stmt, char *statement, MYSQL *conn);
extern void finish_with_error(MYSQL *conn, char *message);
extern void finish_with_stmt_error(MYSQL *conn, MYSQL_STMT *stmt, char *message, bool close_stmt);
extern void set_binding_param(MYSQL_BIND *param, enum enum_field_types type, void *buffer, unsigned long len);
extern void date_to_mysql_time(char *str, MYSQL_TIME *time);
extern void time_to_mysql_time(char *str, MYSQL_TIME *time);
extern void init_mysql_timestamp(MYSQL_TIME *time);
extern void mysql_timestamp_to_string(MYSQL_TIME *time, char *str);
extern void mysql_date_to_string(MYSQL_TIME *date, char *str);
extern void mysql_time_to_string(MYSQL_TIME *time, char *str);

extern int exe_proc(MYSQL_STMT *procedure,  char * buff); 
extern int take_result(MYSQL_STMT *procedure, MYSQL_BIND *param, char *buff); 
extern size_t bind_exe(MYSQL_STMT *procedure, MYSQL_BIND *param, char * buff);
extern void init_mysql_date(MYSQL_TIME *time); 
extern size_t take_rows(MYSQL_STMT *procedure, char *buff); 
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>

/* strtok_r() won't remove the whole ${ part, only the $ */
#define remove_bracket(name) name + 1

#define remove_space(value) value + 1


static char *concat(char *buffer, char *string)
{
	if (!buffer) {
		return strdup(string);
	}
	if (string) {
		size_t length = strlen(buffer) + strlen(string) + 1;
		char *new = realloc(buffer, length);

		return strcat(new, string);
	}

	return buffer;
}

static bool is_nested(char *value)
{
	return strstr(value, "${") && strstr(value, "}");
}

/**
 * @example With TEST_DIR=${BASE_DIR}/.test the first strtok_r call will return
 * BASE_DIR}/.test instead of NULL, or an empty string
 */
static char *prepare_value(char *value)
{
	char *new = malloc(strlen(value) + 2);
	sprintf(new, " %s", value);

	return new;
}

static char *parse_value(char *value)
{
	value = prepare_value(value);

	char *search = value, *parsed = NULL, *tok_ptr;
	char *name;

	if (value && is_nested(value)) {
		while (1) {
			parsed = concat(parsed, strtok_r(search, "${", &tok_ptr));
			name = strtok_r(NULL, "}", &tok_ptr);

			if (!name) {
				break;
			}
			parsed = concat(parsed, getenv(remove_bracket(name)));
			search = NULL;
		}
		free(value);

		return parsed;
	}
	return value;
}

static bool is_commented(char *line)
{
	if ('#' == line[0]) {
		return true;
	}

	int i = 0;
	while (' ' == line[i]) {
		if ('#' == line[++i]) {
			return true;
		}
	}

	return false;
}

static void set_variable(char *name, char *original, bool overwrite)
{
	char *parsed;

	if (original) {
		parsed = parse_value(original);
		setenv(name, remove_space(parsed), overwrite);

		free(parsed);
	}
}

static void parse(FILE *file, bool overwrite)
{
	char *name, *original, *line = NULL, *tok_ptr;
	size_t len = 0;

	while (-1 != getline(&line, &len, file)) {
		if (!is_commented(line)) {
			name = strtok_r(line, "=", &tok_ptr);
			original = strtok_r(NULL, "\n", &tok_ptr);

			set_variable(name, original, overwrite);
		}
	}
	free(line);
}

static FILE *open_default(const char *base_path)
{
	char path[strlen(base_path) + strlen(".env") + 1];
	sprintf(path, "%s/.env", base_path);

	return fopen(path, "rb");
}

int env_load(const char *path, bool overwrite)
{
	FILE *file = open_default(path);

	if (!file) {
		file = fopen(path, "rb");

		if (!file) {
			return -1;
		}
	}
	parse(file, overwrite);
	fclose(file);

	return 0;
}

#ifndef DOTENV_DOTENV_H
#define DOTENV_DOTENV_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @param path Can be a directory containing a file named .env, or the path of the env file itself
 * @param overwrite Existing variables will be overwritten
 * @return 0 on success, -1 if can't open the file
 */
int env_load(const char* path, bool overwrite);

#ifdef __cplusplus
}
#endif

#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <setjmp.h>

#ifdef __unix__
#include <termios.h>
#endif

#include "io.h"

jmp_buf leave_buff;
bool io_initialized;

static void leave(void)
{
	if(io_initialized)
		longjmp(leave_buff, 1);
	else
		exit(EXIT_SUCCESS);
}

char *get_input(char *question, int len, char *buff, bool hide)
{
	printf("%s", question);

#ifdef __unix__
	struct termios term, oterm;

	if(hide) {
		fflush(stdout);
		if (tcgetattr(fileno(stdin), &oterm) == 0) {
			memcpy(&term, &oterm, sizeof(struct termios));
			term.c_lflag &= ~(ECHO|ECHONL);
			tcsetattr(fileno(stdin), TCSAFLUSH, &term);
		} else {
			memset(&term, 0, sizeof(struct termios));
			memset(&oterm, 0, sizeof(struct termios));
		}
	}
#else
	// Look at termio.h on MSDN to implement similar functionality on Windows
	(void)hide;
#endif

	if(fgets(buff, len, stdin) != NULL) {
		buff[strcspn(buff, "\n")] = 0;
	} else {
		printf("EOF received, leaving...\n");
		fflush(stdout);
		leave();
	}

	// Empty stdin
	if(strlen(buff) + 1 == len) {
		int ch;
		while(((ch = getchar()) != EOF) && (ch != '\n'));
		if(ch == EOF) {
			printf("EOF received, leaving...\n");
			fflush(stdout);
			leave();
		}
	}

#ifdef __unix__
	if(hide) {
		fwrite("\n", 1, 1, stdout);
		tcsetattr(fileno(stdin), TCSAFLUSH, &oterm);
	}
#endif

	return buff;
}


bool yes_or_no(char *question, char yes, char no, bool default_answer, bool insensitive)
{
	int extra;

	// yes and no characters should be lowercase by default
	yes = (char)tolower(yes);
	no = (char)tolower(no);

	// Which of the two is the default?
	char s, n;
	if(default_answer) {
		s = (char)toupper(yes);
		n = no;
	} else {
		s = yes;
		n = (char)toupper(no);
	}

	while(true) {
		printf("%s [%c/%c]: ", question, s, n);
		extra = 0;

		char c = (char)getchar();
		char ch = 0;
		if(c != '\n') {
			while(((ch = (char)getchar()) != EOF) && (ch != '\n'))
				extra++;
		}
		if(c == EOF || ch == EOF) {
			printf("EOF received, leaving...\n");
			fflush(stdout);
			leave();
		}
		if(extra > 0)
			continue;

		// Check the answer
		if(c == '\n') {
			return default_answer;
		} else if(c == yes) {
			return true;
		} else if(c == no) {
			return false;
		} else if(c == toupper(yes)) {
			if(default_answer || insensitive) return true;
		} else if(c == toupper(no)) {
			if(!default_answer || insensitive) return false;
		}
	}
}


char multi_choice(char *question, const char choices[], int num)
{
	char possibilities[2 * num * sizeof(char)];
	int i, j = 0, extra;
	for(i = 0; i < num; i++) {
		possibilities[j++] = choices[i];
		possibilities[j++] = '/';
	}
	possibilities[j - 1] = '\0'; // Remove last '/'

	while(true) {
		printf("%s [%s]: ", question, possibilities);

		extra = 0;
		char c = (char)getchar();
		if(c == '\n')
			continue;
		char ch;
		while(((ch = (char)getchar()) != EOF) && (ch != '\n'))
			extra++;
		if(c == EOF || ch == EOF) {
			printf("EOF received, leaving...\n");
			fflush(stdout);
			leave();
		}
		if(extra > 1) // Need exactly one character on stdin
			continue;

		// Check if the choice is valid
		for(i = 0; i < num; i++) {
			if(c == choices[i])
				return c;
		}
	}
}


void clear_screen(void)
{
	// To whom it may interest: this "magic" is a sequence of escape codes from VT100 terminals:
	// https://www.csie.ntu.edu.tw/~r92094/c++/VT100.html
	printf("\033[2J\033[H");
}

void press_anykey(void)
{
	char c;
	puts("\nPress any key to continue...");
	while((c = (char)getchar()) != '\n');
	(void)c;
}
#pragma once
#include <stdbool.h>
#include <setjmp.h>

extern jmp_buf leave_buff;
extern bool io_initialized;


#define initialize_io()                    \
__extension__ ({                           \
	io_initialized = true;             \
	int __ret = setjmp(leave_buff);    \
	__ret == 0;                        \
})

extern char *get_input(char *question, int len, char *buff, bool hide);
extern bool yes_or_no(char *question, char yes, char no, bool default_answer, bool insensitive);
extern char multi_choice(char *question, const char choices[], int num);
extern void clear_screen(void);
extern void press_anykey(void);
#include <stdbool.h>
#include <stdlib.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "validation.h"

regex_t regex_date;
regex_t regex_time;
regex_t regex_integer; 
regex_t regex_double; 

static void print_regerror(int errcode, size_t length, regex_t *compiled)
{
	char buffer[length];
	(void) regerror(errcode, compiled, buffer, length);
	fprintf(stderr, "Regex match failed: %s\n", buffer);
}

/**
* Consente di effettuare il setting della struttura regex_t, secondo il pattern desiderato.
* In caso di mancanza di memoria (REG_ESPACE) varrà stampato un messaggio d'errore indicante
* il nome della regex. Ritorna il risultato dell'istruzione regcomp().
*/
int setting_regex(regex_t *regex , char *pattern_to_match, char *regex_name){
	int result = regcomp(regex, pattern_to_match, REG_EXTENDED);
	if (result){
		if (result == REG_ESPACE){
			fprintf(stderr, "%s\n", strerror(ENOMEM));
		}
		else {
			fprintf(stderr, "Fatal error while setting up %s regex.\n",regex_name);
		}
	}
	return result;
}

/**
* Inizializza tutte le strutture regex_t utili al programma.
* Ritorna TRUE se tutte le strutture regex_t sono state inizializzate correttamente, altrimenti ritorna FALSE alla prima
* regex_t nopn correttamente inizializzata.
*/
bool init_validation(void)
{
	if (setting_regex(&regex_date, "^([12][0-9]{3}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01]))", "date validation")){
		return false;
	}

	if (setting_regex(&regex_time, "^([0-1]?[0-9]|2?[0-3]|[0-9]):([0-5][0-9]|[0-9])", "time validation")){
		return false;
	}

	if (setting_regex(&regex_integer,"^\\d", "integer number validation")){
		return false;
	}
	
	if (setting_regex(&regex_double,"^[0-9]+(\\.[0-9]+)?", "double number validation")){
		return false;
	}


	return true;
}

/**
* Metodo di validazione generico delle stringhe inserite dall'utente. La funzione
* ottiene in input la stringa e la struttura regex_t contenente il pattern di confronto da utilizzare.
* Ritorna TRUE se il valori di ritorno di regexec è uguale a 0, in caso contrario
* stampa un messaggio d'errore indicante la regex fallita.
*/
bool validate(char *str, regex_t *regex){

	init_validation();
	int ret = regexec(regex, str, 0, NULL, REG_NOTEOL);

	if(ret != 0 && ret != REG_NOMATCH) {
		size_t length = regerror(ret, regex, NULL, 0);
		print_regerror(ret, length, regex);
		return false;
	}

	fini_validation(); 

	return ret == 0;
}

bool validate_date(char *str)
{
	return validate(str, &regex_date);
	free(&regex_date); 
}

bool validate_time(char *str)
{
	return validate(str, &regex_time);
}

bool validate_integer(char *str){
	return validate(str, &regex_integer);
}

bool validate_double(char *str){
	return validate(str, &regex_double);
}


/**
* Libera la memoria allocata per le strutture regex_t allocate.
*/
void fini_validation(void)
{
	regfree(&regex_time);
	regfree(&regex_date);
	regfree(&regex_integer);
	regfree(&regex_double);
}
#pragma once

#include <stdbool.h>
#include <regex.h>

int setting_regex(regex_t *regex , char *pattern_to_match, char *regex_name);
extern bool init_validation(void);
bool validate(char *str, regex_t *regex);
extern bool validate_time(char *str);
extern bool validate_date(char *str);
extern bool validate_integer(char *str);
extern bool validate_double(char *str);
extern void fini_validation(void);
