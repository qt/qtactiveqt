TEMPLATE = subdirs

CONFIG	+= ordered
axshared.file = axshared.prx
SUBDIRS = axshared container
!wince*: SUBDIRS += control

