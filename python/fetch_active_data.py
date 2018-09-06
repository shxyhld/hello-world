#!/usr/bin/python
# -*- coding: UTF-8 -*-
import MySQLdb

# 打开数据库连接
host = "localhost"
user = "test"
pwd = "123456"
db_name = "test_table"
db = MySQLdb.connect(host, user, pwd, db_name, charset='utf8' )
# 使用cursor()方法获取操作游标 
cursor = db.cursor()

d = {}
def get_key(flag, zhuang_count):
  return str(flag) + "renwanfa_lianzhuancount" + str(zhuang_count)

def insert_value(key, value):
  if d.has_key(key):
    d[key] += value
  else:
    d[key] = value

def print_dict():
  for k,v in d.items():
    print "%s,%d" % (k,v)

def fetch_data(max_circle):
  sqlStr="select DeskId,CurCircle,Zhuang,Flag as cnt from video where MaxCircle = " + str(max_circle) + " and Flag >=0 and Flag < 3 and Time > UNIX_TIMESTAMP() - 24*60*60 ORDER BY DeskID,CurCircle;"
  print (sqlStr)
  # 使用execute方法执行SQL语句
  cursor.execute(sqlStr)
  results = cursor.fetchall()
  last_desk_id = 0
  last_zhuang_pos = 0
  zhuang_count = 1
  for row in results:
    DeskId = row[0]
    CurCircle = row[1]
    Zhuang = row[2]
    flag = row[3]
    if DeskId != last_desk_id:
      insert_value(get_key(4-flag,zhuang_count),1)
      last_desk_id = DeskId    
      zhuang_count = 1
      last_zhuang_pos = Zhuang
    elif Zhuang != last_zhuang_pos:
      insert_value(get_key(4-flag,zhuang_count),1)
      zhuang_count = 1
      last_zhuang_pos = Zhuang
    else:
      zhuang_count += 1
  return

def test_connection():
  sqlStr="select version();"
  cursor.execute(sqlStr)
  results = cursor.fetchone()
  print "results=%s" % results
  return

if __name__ == "__main__":
  #test_connection()
  fetch_data(8)
  fetch_data(16)
  print_dict()
  db.close()
