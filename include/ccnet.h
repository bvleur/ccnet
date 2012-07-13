/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#ifndef _CCNET_H
#define _CCNET_H

#include <ccnet/option.h>

#include <glib.h>

#include <ccnet/valid-check.h>
#include <ccnet/peer.h>
#include <ccnet/message.h>
#include <ccnet/status-code.h>
#include <ccnet/processor.h>

#include <ccnet/ccnet-session-base.h>
#include <ccnet/ccnet-client.h>

#include <ccnet/proc-factory.h>
#include <ccnet/sendcmd-proc.h>
#include <ccnet/mqclient-proc.h>
#include <ccnet/invoke-service-proc.h>

#include <ccnet/timer.h>


/* mainloop */

void ccnet_main (CcnetClient *client);

typedef void (*RegisterServiceCB) (gboolean success);
void ccnet_register_service (CcnetClient *client,
                             const char *service, const char *group,
                             GType proc_type, RegisterServiceCB cb);
CcnetClient *ccnet_init (const char *confdir);

void ccnet_send_command (CcnetClient *client, const char *command,
                         SendcmdProcRcvrspCallback cmd_cb, void *cbdata);

void ccnet_add_peer (CcnetClient *client, const char *id, const char *addr);

void ccnet_connect_peer (CcnetClient *client, const char *id);
void ccnet_disconnect_peer (CcnetClient *client, const char *id);


/* rpc wrapper */

#include <searpc-client.h>

SearpcClient *
ccnet_create_rpc_client (CcnetClient *cclient, const char *peer_id,
                         const char *service_name);

SearpcClient *
ccnet_create_async_rpc_client (CcnetClient *cclient, const char *peer_id,
                               const char *service_name);

void ccnet_rpc_client_free (SearpcClient *client);
void ccnet_async_rpc_client_free (SearpcClient *client);

CcnetPeer *ccnet_get_peer (SearpcClient *client, const char *peer_id);
CcnetPeer *ccnet_get_peer_by_idname (SearpcClient *client, const char *idname);
int ccnet_get_peer_net_state (SearpcClient *client, const char *peer_id);
int ccnet_get_peer_bind_status (SearpcClient *client, const char *peer_id);
CcnetPeer *ccnet_get_default_relay (SearpcClient *client);
GList *ccnet_get_peers_by_role (SearpcClient *client, const char *role);

char *ccnet_get_binding_email (SearpcClient *client, const char *peer_id);
GList *ccnet_get_groups_by_user (SearpcClient *client, const char *user);
GObject *ccnet_get_org_by_user (SearpcClient *client, const char *user);

int
ccnet_get_binding_email_async (SearpcClient *client, const char *peer_id,
                               AsyncCallback callback, void *user_data);

char *ccnet_sign_message (SearpcClient *client, const char *message);
int ccnet_verify_message (SearpcClient *client,
                          const char *message,
                          const char *sig_base64,
                          const char *peer_id);

char *ccnet_get_config (SearpcClient *client, const char *key);
int ccnet_set_config (SearpcClient *client, const char *key, const char *value);

void
ccnet_login_to_relay (SearpcClient *client, const char *relay_id,
                      const char *username, const char *passwd);


#endif
