using UnityEditor.ShaderGraph.Internal;
using UnityEngine;

public class Turret : MonoBehaviour
{
    [SerializeField] private int m_Damage = 10;
    [SerializeField] private float m_FireRate = 1f;
    [SerializeField] private float m_Cooldown = 0f;
    [SerializeField] private GameObject m_Bullet = null;
    Machine m_Machine = null;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        m_Machine = transform.parent.gameObject.transform.Find("Machine").gameObject.GetComponent<Machine>();
    }

    GameObject GetTarget()
    {
        GameObject[] candidats = Object.FindObjectsByType<GameObject>(FindObjectsSortMode.None);

        GameObject plusProche = null;
        float distanceMinimale = Mathf.Infinity;
        int layerCible = LayerMask.NameToLayer("Zombies");

        foreach (GameObject candidat in candidats)
        {
            // 2. On vérifie si l'objet a le bon layer
            if (candidat.layer == layerCible)
            {
                // 3. Calcul de la distance entre la source et le candidat
                float distance = (candidat.transform.position - transform.position).sqrMagnitude;

                if (distance < distanceMinimale)
                {
                    distanceMinimale = distance;
                    plusProche = candidat;
                }
            }
        }

        return plusProche;
    }

    void Shoot()
    {
        if(m_Machine == null)
            m_Machine = transform.parent.gameObject.transform.Find("Machine").gameObject.GetComponent<Machine>();

        if (m_Cooldown >= m_FireRate && m_Machine != null)
        {
            // SHOOT
            if (m_Machine.outputSlot.amount > 0)
            {
                m_Machine.outputSlot.amount -= 1;
                GameObject target = GetTarget();
                if(target == null)
                    Debug.Log("No target found");
                GameObject m_preview = Instantiate(m_Bullet, transform.position, Quaternion.identity);
                m_preview.GetComponent<BulletScript>().m_pTarget = target;

                m_Cooldown = 0f;
            }               
        }
        else
        {
            m_Cooldown += Time.deltaTime;
        }
    }

    // Update is called once per frame
    void Update()
    {
        Shoot();
    }
}
