using System.Collections;
using Unity.Mathematics;
using UnityEngine;


public class Spawn : MonoBehaviour
{
    // POSSIBLE MOB TO SPAWN
    [SerializeField] private GameObject[] spawnable;
    [SerializeField] private float2 m_PossibleSpeed = new float2(0f, 0f);
    [SerializeField] private LayerMask m_SpawnLayer;
    [SerializeField] private float m_HP = 1f;

    /// METHODS
    void Start()
    {
        StartCoroutine(SpawnLoop());
    }

    /// COROUTINES
    IEnumerator SpawnLoop()
    {
        while(true)
        {
            //int randomMobIndex = Random.Range(0, spawnable.Length);

            //MeshRenderer prefabMeshRenderer = spawnable[randomMobIndex].GetComponentInChildren<MeshRenderer>();
            Vector3 prefabSize = Vector3.zero;


            GameObject capsule = GameObject.CreatePrimitive(PrimitiveType.Capsule);
            MeshRenderer prefabMeshRenderer = capsule.GetComponentInChildren<MeshRenderer>();
            ZombieMovement zombieMovement = capsule.AddComponent<ZombieMovement>();
            capsule.AddComponent<Health>().SetHealt(m_HP);
            capsule.AddComponent<Rigidbody>();
            capsule.layer = (int)Mathf.Log(m_SpawnLayer.value, 2);
            capsule.name = "Zombie";

            zombieMovement.m_MinimumSpeed = m_PossibleSpeed.x;
            zombieMovement.m_MaximumSpeed = m_PossibleSpeed.y;

            if (prefabMeshRenderer != null)
            {
                prefabSize = prefabMeshRenderer.bounds.size / 2f;
                prefabSize = new Vector3(prefabSize.x, prefabSize.z, prefabSize.y);
            }
            
            Vector3 size = transform.localScale;
            //size = new Vector3(size.x / 10f, size.z / 10f, size.y / 10f);
            size = size / 2f;

            float randomX = UnityEngine.Random.Range(-size.x + prefabSize.x, size.x - prefabSize.x);
            float randomY = UnityEngine.Random.Range(-size.y + prefabSize.y, size.y - prefabSize.y);
            float randomZ = UnityEngine.Random.Range(-size.z + prefabSize.z, size.z - prefabSize.z);
            Vector3 randomPos = new Vector3(randomX, randomY, randomZ);

            // FOR TEST
            capsule.transform.position = transform.position + randomPos;


            // FOR PREFAB
            //Instantiate(spawnable[randomMobIndex], randomPos, Quaternion.identity);
            yield return new WaitForSeconds(2.5f);
        }
    }
}
