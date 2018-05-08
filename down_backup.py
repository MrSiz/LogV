import paramiko

def work():
	log_server_path = '/usr/local/nginx/logs/access.log'
	log_store_path = '/home/mrsiz/test.log'
	hname = '118.89.243.43'
	uname = 'ubuntu'
	pwd ='xxxxxx'
	cnt = 500
	
	
	client = paramiko.SSHClient()
	client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
	client.connect(hostname=hname, port=22, username=uname, password=pwd)

	cmd = 'tail -n ' + str(cnt) + ' ' + log_server_path + ' > ' + '/tmp/temp.log'
	
	stdin, stdout, stderr = client.exec_command(cmd)
	
	
	trans = client.get_transport()
	sftp = paramiko.SFTPClient.from_transport(trans)

	sftp.get('/tmp/temp.log', log_store_path)
	
	client.close()
	return 11;
	
if __name__ == '__main__':
	res = work()
	print res
