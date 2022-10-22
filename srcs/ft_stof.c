#include "minirt.h"

//convert string to float

static long	ft_power(int base, int exponent)
{
    long	power;

    power = 1;
    while (exponent > 0)
    {
        power = power * base;
        exponent--;
    }
    return (power);
}

bool	ft_string_digit(char *str)
{
    int	i;

    i = 0;
    while (str[i] != '\0')
    {
        if (!ft_isdigit(str[i]) && str[i] != '\n')
            return (false);
        i++;
    }
    return (true);
}

static float	ft_convert(int deci_places, char *tmp, char *tmp2)
{
    float	result;
    long	power;
    int		int1;
    int		int2;

    if (!ft_string_digit(tmp2))
    {
        ft_free(tmp);
        ft_free(tmp2);
        msg_error("Float input is wrong", NULL);
    }
    int1 = ft_atoi(tmp);
    int2 = ft_atoi(tmp2);
    power = int1 * ft_power(10, deci_places);
    if (power >= 0)
        power = power + int2;
    else
        power = power - int2;
    result = (float)power / (float)(ft_power(10, deci_places));
    if (ft_strncmp(tmp, "-0", 2) == 0)
        result = -result;
    ft_free(tmp);
    ft_free(tmp2);
    return (result);
}

float	ft_stof(char *str)
{
    int		deci_sepa;
    int		i;
    char	*tmp;
    char	*tmp2;

    i = 0;
    deci_sepa = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '.')
        {
            deci_sepa = i;
            break ;
        }
        i++;
    }
    if (str[i] == '\0')
    {
        tmp2 = ft_strdup("0");
        deci_sepa = i;
    }
    else
        tmp2 = ft_substr(str, deci_sepa + 1, ft_strlen(str) - deci_sepa);
    tmp = ft_substr(str, 0, deci_sepa);
    return (ft_convert(ft_strlen(tmp2), tmp, tmp2));
}