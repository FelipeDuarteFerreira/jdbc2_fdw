/*-------------------------------------------------------------------------
 *
 * jdbc2_fdw.h
 *        Foreign-data wrapper for remote PostgreSQL servers
 *
 * Portions Copyright (c) 2012-2014, PostgreSQL Global Development Group
 *
 * IDENTIFICATION
 *        contrib/jdbc2_fdw/jdbc2_fdw.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef JDBC2_FDW_H
#define JDBC2_FDW_H

#include "foreign/foreign.h"
#include "lib/stringinfo.h"
#include "nodes/pathnodes.h"
#include "utils/rel.h"

#include "libpq-fe.h"
#include "jq.h"

/* in jdbc2_fdw.c */
extern int  set_transmission_modes(void);
extern void reset_transmission_modes(int nestlevel);

/* in connection.c */
extern Jconn *GetConnection(ForeignServer *server, UserMapping *user,
              bool will_prep_stmt);
extern void ReleaseConnection(Jconn *conn);
extern unsigned int GetCursorNumber(Jconn *conn);
extern unsigned int GetPrepStmtNumber(Jconn *conn);
extern void pgfdw_report_error(int elevel, Jresult *res, Jconn *conn,
                   bool clear, const char *sql);

/* in option.c */
extern int ExtractConnectionOptions(List *defelems,
                         const char **keywords,
                         const char **values);

/* in deparse.c */
extern void classifyConditions(PlannerInfo *root,
                   RelOptInfo *baserel,
                   List *input_conds,
                   List **remote_conds,
                   List **local_conds);
extern bool is_foreign_expr(PlannerInfo *root,
                RelOptInfo *baserel,
                Expr *expr);
extern void deparseSelectSql(StringInfo buf,
                 PlannerInfo *root,
                 RelOptInfo *baserel,
                 Bitmapset *attrs_used,
                 List **retrieved_attrs);
extern void appendWhereClause(StringInfo buf,
                  PlannerInfo *root,
                  RelOptInfo *baserel,
                  List *exprs,
                  bool is_first,
                  List **params);
extern void deparseInsertSql(StringInfo buf, PlannerInfo *root,
                 Index rtindex, Relation rel,
                 List *targetAttrs, List *returningList,
                 List **retrieved_attrs);
extern void deparseUpdateSql(StringInfo buf, PlannerInfo *root,
                 Index rtindex, Relation rel,
                 List *targetAttrs, List *returningList,
                 List **retrieved_attrs);
extern void deparseDeleteSql(StringInfo buf, PlannerInfo *root,
                 Index rtindex, Relation rel,
                 List *returningList,
                 List **retrieved_attrs);
extern void deparseAnalyzeSizeSql(StringInfo buf, Relation rel);
extern void deparseAnalyzeSql(StringInfo buf, Relation rel,
                  List **retrieved_attrs);

#endif   /* JDBC2_FDW_H */
