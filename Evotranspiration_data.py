# -*- coding: utf-8 -*-
"""
Created on Wed Jan 29 17:17:58 2020

@author: hp
"""

import pandas as pd

def findValue(month, df, start, end):
    tmax = sum(df.loc[start:end, 'temperatureMax'])
    tmin = sum(df.loc[start:end, 'temperatureMin'])
    tmean = (tmax + tmin)/month/2
    tmeaninC = (5/9)*(tmean - 32)
    sunrise = sum(df.loc[start:end, 'sunriseTime'])
    sunset = sum(df.loc[start:end, 'sunsetTime'])
    p = (sunset - sunrise)/86400/month
    return tmeaninC, p

df = pd.read_csv('year_2018.csv')
df1 = pd.read_csv('year_2019.csv')
months = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
start = -31
end = 1
df2 = []
for month in months:
    start += month
    end += month
    tmean1 , p1 = findValue(month, df, start, end)
    tmean2 , p2 = findValue(month, df1, start, end)
    tmean = (tmean1 + tmean2)/2
    p = (p1 + p2)/2
    df2.append([tmean, p])
df2 = pd.DataFrame(df2, columns=['Tmean', 'p'])
df2.to_csv('ET0.csv', index=False)