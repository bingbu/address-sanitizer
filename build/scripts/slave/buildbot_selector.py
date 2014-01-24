#!/usr/bin/python

import os
import subprocess
import sys

THIS_DIR=os.path.dirname(sys.argv[0])


def bash(path):
    return 'bash ' + os.path.join(THIS_DIR, path)

def cmd_call(path):
    return 'call ' + os.path.join(THIS_DIR, path)

BOT_ASSIGNMENT = {
    'win': cmd_call('buildbot_standard.bat'),
    'linux': bash('buildbot_standard.sh'),
    'linux-cmake': bash('buildbot_cmake.sh'),
    'linux-bootstrap': bash('buildbot_bootstrap.sh'),
    'linux-chrome-asan': bash('buildbot_chrome_asan.sh'),
    'linux-chrome-tsan': bash('buildbot_chrome_tsan.sh'),
    'linux-perf-asan': bash('buildbot_perf_asan.sh'),
    'mac10.8-cmake': bash('buildbot_cmake.sh'),
    'mac10.8': bash('buildbot_standard.sh'),
    'sanitizer-x86_64-linux': bash('buildbot_cmake.sh'),
    'sanitizer-x86_64-linux-bootstrap': bash('buildbot_bootstrap.sh'),
}

BOT_ADDITIONAL_ENV = {
    'win': {},
    'linux': { 'CHECK_TSAN': '1' },
    'linux-cmake': {},
    'linux-bootstrap': {},
    'linux-chrome-asan': {},
    'linux-chrome-tsan': {},
    'linux-perf-asan': {},
    'mac10.8-cmake': { 'MAX_MAKE_JOBS': '4' },
    'mac10.8': { 'MAX_MAKE_JOBS': '4' },
    'sanitizer-x86_64-linux': { 'BUILD_ANDROID' : '1', 'RUN_ANDROID' : '1' },
    'sanitizer-x86_64-linux-bootstrap': {},
}

def Main():
  builder = os.environ.get('BUILDBOT_BUILDERNAME')
  print "builder name: %s" % (builder)
  cmd = BOT_ASSIGNMENT.get(builder)
  if not cmd:
    sys.stderr.write('ERROR - unset/invalid builder name\n')
    sys.exit(1)

  print "%s runs: %s\n" % (builder, cmd)
  sys.stdout.flush()

  bot_env = os.environ
  add_env = BOT_ADDITIONAL_ENV.get(builder)
  for var in add_env:
    bot_env[var] = add_env[var]
  if 'TMPDIR' in bot_env:
    del bot_env['TMPDIR']

  retcode = subprocess.call(cmd, env=bot_env, shell=True)
  sys.exit(retcode)


if __name__ == '__main__':
  Main()
