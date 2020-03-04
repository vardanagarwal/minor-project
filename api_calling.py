# -*- coding: utf-8 -*-
"""
Created on Mon Jan 13 16:31:54 2020

@author: hp
"""

import requests
import pandas as pd
from collections import namedtuple


df1 = []
features = ['temperatureMin', 
            'temperatureMax',
            'sunriseTime',
            'sunsetTime']
DailySummary = namedtuple("DailySummary", features)
i = 1
for unix in range(1546300800, 1577836800, 86400):
    BASE_URL = "https://api.darksky.net/forecast/0d3b960fe7362e11cc9f6213b6fc192a/26.8371648,75.5625925," + str(unix) + "?exclude=currently,flags,alerts"
    response = requests.get(BASE_URL)
    data = response.json()
    df = pd.DataFrame(data["daily"]["data"])
    df1.append(DailySummary(temperatureMin = df.at[0, 'temperatureMin'],
                            temperatureMax = df.at[0, 'temperatureMax'],
                            sunriseTime = df.at[0, 'sunriseTime'],
                            sunsetTime = df.at[0, 'sunsetTime']))
    print(i)
    i += 1
res = pd.DataFrame(df1, columns=features)
print('last')
res.to_csv('year_2019.csv', index=False)

#%%


def fn1():
    list1 = [1, 2, 3] 
    list2 = list1 
    print(id(list1), id(list2))
    list1 += ['a', 'b', 'c']
    print(id(list1), id(list2))
    
def fn2():
    list1 = [1, 2, 3] 
    list2 = list1 
    print(id(list1), id(list2))
    list1 = list1 + ['a', 'b', 'c']
    print(id(list1), id(list2))
    
print('calling first function')
fn1()
print('calling second function')
fn2()