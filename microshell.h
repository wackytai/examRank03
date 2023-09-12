/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:45:47 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/12 14:33:12 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <dirent.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>

int	error_message(char *str, char *s1);
int	ft_cd(char **argv, int i);
int	ft_executer(char **argv, int i, char **envp);
int	main(int argc, char **argv, char **envp);

#endif