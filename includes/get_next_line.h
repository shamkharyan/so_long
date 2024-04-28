/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:15:57 by pshamkha          #+#    #+#             */
/*   Updated: 2024/04/26 19:02:20 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include "../ft_printf/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*get_linef(char *file);
char	*set_file(char *file);
char	*get_file(int fd, char *file);
char	*join_free(char *file, char *buff);

#endif
